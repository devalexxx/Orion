//
// Created by Alex on 01/02/2024.
//

#include "doctest/doctest.h"
#include "orion/core.h"

namespace orion {

    template<>
    class System<int> : public ISystem {
    public:
        using Functor = Functor<int>;
        explicit System(Functor&& fn) : m_fn(fn) {}
        void execute(RefMut<World> world) override {
            m_fn(5);
        }
    private:
        Functor m_fn;
    };

    template<>
    class System<void> : public ISystem {
    public:
        void execute(RefMut<World> world) override {
            std::cout << ++m_i << "\n";
        }
    private:
        i32 m_i = 0;
    };

    class CustomSystem : public ISystem {
    public:
        using FnPtr = void(*)(RefMut<World>, i32);
        using Fn    = std::function<void(RefMut<World>, i32)>;

        explicit CustomSystem(FnPtr fn, int value) : m_fn(fn), m_value(value) {}
        void execute(RefMut<World> world) override {
            m_fn(world, m_value);
            m_value++;
        }
    private:
        Fn  m_fn;
        i32 m_value;
    };

}

TEST_SUITE("ecs") {
    using orion::Include;
    using orion::Exclude;
    using orion::Marker;
    using orion::Query;
    using orion::World;
    using orion::RefMut;

    struct Point {
        int x, y;
    };

    struct Tag {};

    void on_update(RefMut<World> world) {
        std::cout << "Sys update\n";
    }

    TEST_CASE("world") {
        World world;

        auto& entity = world.create_entity();

        world.emplace_component<Point>(entity, 3, 2);
        world.emplace_component<Point>(entity);;
        world.emplace_component<Tag>(entity);

        world.remove_component<Point>(entity);

        world.emplace_system(on_update);

        world.update();

        world.update();

    }

    TEST_CASE("type_info") {

        orion::TypeInfo<int&> ti;

        std::cout << "is ref : " << ti.is_ref << "\n";
        std::cout << "is const : " << ti.is_const << "\n";

        Include<int&, const char&, float&, Marker<int>> include;

        Exclude<int, const float, int*> exclude;

        exclude.foreach([](const auto& elem, size_t i) {std::cout << "const : " << elem.is_const << ", ref : " << elem.is_ref << "\n";});
        std::cout << "\n";
        include.foreach([](const auto& elem, size_t i) {std::cout << "const : " << elem.is_const << ", ref : " << elem.is_ref << ", marker : " << elem.is_marker << "\n";});

    }

    TEST_CASE("query") {

        orion::World world;

        auto& e1 = world.create_entity();
        world.emplace_component<Point>(e1, 3, 2);
        world.emplace_component<Tag>(e1);

        auto& e2 = world.create_entity();
        world.emplace_component<Point>(e2, 8, 1);

        auto& e3 = world.create_entity();
        world.emplace_component<Point>(e3, 12, 21);
        world.emplace_component<Tag>(e3);

        Query<Include<Point&>, Exclude<Tag>> query(world);

        for (auto& [entity, components]: query.iter()) {
            auto& [point] = components;
            std::cout << "Entity " << entity.get_index() << ":" << entity.get_version();
            std::cout << ", x : " << point.x << ", y : " << point.y << "\n";
            point.x = 10;
        }

        for (auto& [entity, components]: query.iter()) {
            auto& [point] = components;
            std::cout << "Entity " << entity.get_index() << ":" << entity.get_version();
            std::cout << ", x : " << point.x << ", y : " << point.y << "\n";
        }

        Query<Include<Point&>, Exclude<Tag>> query2(world);

        for (auto& [entity, components]: query2.iter()) {
            auto& [point] = components;
            std::cout << "Entity " << entity.get_index() << ":" << entity.get_version();
            std::cout << ", x : " << point.x << ", y : " << point.y << "\n";
        }

    }

    void point_system(RefMut<World> world) {
        std::cout << "WorldSystem\n";

        auto query = world.query<Include<const Point&, Marker<Tag>>>();

        for (auto& [entity, components]: query.iter()) {
            auto& [point] = components;
            std::cout << "Entity " << entity.get_index() << ":" << entity.get_version();
            std::cout << ", x : " << point.x << ", y : " << point.y << "\n";
        }
    }

    void point_system_direct_query(Query<Include<const Point&, Marker<Tag>>> query) {
        std::cout << "QuerySystem\n";
        for (auto& [entity, components]: query.iter()) {
            auto& [point] = components;
            std::cout << "Entity " << entity.get_index() << ":" << entity.get_version();
            std::cout << ", x : " << point.x << ", y : " << point.y << "\n";
        }
    }

    TEST_CASE("world_query") {

        World world;

        auto& e1 = world.create_entity();
        world.emplace_component<Point>(e1, 3, 2);
        world.emplace_component<Tag>(e1);

        auto& e2 = world.create_entity();
        world.emplace_component<Point>(e2, 8, 1);

        world.emplace_system(point_system);

        world.emplace_system(point_system_direct_query);

        auto query = world.query<Include<Point&, Marker<Tag>>>();

        for (auto& [entity, components]: query.iter()) {
            auto& [point] = components;
            std::cout << "Entity " << entity.get_index() << ":" << entity.get_version();
            std::cout << ", x : " << point.x << ", y : " << point.y << "\n";
            point.x = 42;
            point.y = 21;
        }

        std::cout << "\n";

        world.update();
    }

    void print_alive_entities(RefMut<World> world) {
        for (auto& entity: world.entities()) {
            if (entity.is_alive())
                std::cout << "Entity " << entity.get_index() << ":" << entity.get_version() << "\n";
        }
        std::cout << "\n";
    }

    TEST_CASE("entity_alive") {
        World world;

        auto to_del1= world.create_entity();
        auto to_del2= world.create_entity();
        auto to_del3= world.create_entity();

        world.emplace_system(print_alive_entities);

        world.update();

        world.kill_entity(to_del1);
        world.kill_entity(to_del3);

        world.update();

        world.create_entity();

        world.update();

        world.kill_entity(to_del1);

        world.update();

        world.create_entity();
        world.create_entity();
        world.create_entity();

        world.update();
    }

    void user_defined_system(int i) {
        std::cout << i << "\n";
    }

    TEST_CASE("user_defined_system") {
        orion::World world;

        world.emplace_system(user_defined_system);

        world.update();
    }

    void first_sys(World&) {
        std::cout << "first\n";
    }

    void last_sys(World&) {
        std::cout << "last\n";
    }

    void last2_sys(World&) {
        std::cout << "last2\n";
    }

    TEST_CASE("system_sorting") {
        orion::World world;

//        world.emplace_system(last_sys).set_priority(0);
//        world.emplace_system(last_sys).set_priority(0);
//        world.emplace_system(first_sys).set_priority(0);

        world.emplace_system(last2_sys).set_name("last2").set_after("first");
        world.emplace_system(last_sys).set_name("last").set_after("first");
        world.emplace_system(first_sys).set_name("first").set_priority(1);

        world.update();
    }

    TEST_CASE("unregister_component") {
        orion::World world;

        auto e0 = world.create_entity();
        world.emplace_component<int>(e0);

        auto q = world.query<Include<float&>>();

    }

    void custom_system(RefMut<World> world, int value) {
        std::cout << value << "\n";
    }

    TEST_CASE("system_obj") {
        orion::World world;

        world.emplace_system<orion::System<void>>();
        world.emplace_system(first_sys);
        world.emplace_system<orion::CustomSystem>(custom_system, 5);

        world.update();
        world.update();
        world.update();
    }

}