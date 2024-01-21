//
// Created by Alex on 15/11/2023.
//

#include "doctest/doctest.h"

#include "orion/core.h"

TEST_SUITE("Event") {

    struct TestStringEvent {
        std::string str;
    };

    void onTestString(const TestStringEvent& event) {
        CHECK_EQ("42", event.str);
    }

    struct TestIntEvent {
        int value;
    };

    void onTestInt(const TestIntEvent& event) {
        CHECK_EQ(42, event.value);
    }

    TEST_CASE("EventManager") {
        auto em = orion::EventManager::create();
        em->subscribe<TestStringEvent>(onTestString);
        {
            em->subscribe<TestIntEvent>(onTestInt);

            TestStringEvent se = {"42"};
            em->emit(se);
        }

        TestIntEvent ie = {42};
        em->emit(ie);
    }

    class AbstractTestEventListener : public orion::EventListener {
    public:
        explicit AbstractTestEventListener(const std::shared_ptr<orion::EventManager>& e_manager) : EventListener(e_manager) {
            bind(&AbstractTestEventListener::onTestString);
            bind(&AbstractTestEventListener::onTestInt);
        }

        virtual void onTestString   (const TestStringEvent& event)  {};
        virtual void onTestInt      (const TestIntEvent& event)     {};

    };

    class TestEventListener_1 : AbstractTestEventListener {
    public:
        explicit TestEventListener_1(const std::shared_ptr<orion::EventManager>& e_manager) : AbstractTestEventListener(e_manager) {}

        void onTestString(const TestStringEvent &event) override {
            CHECK_EQ("42", event.str);
        }

        void onTestInt(const TestIntEvent &event) override {
            CHECK_EQ(42, event.value);
        }
    };

    class TestEventListener_2 : AbstractTestEventListener {
    public:
        explicit TestEventListener_2(const std::shared_ptr<orion::EventManager>& e_manager) : AbstractTestEventListener(e_manager) {}

        void onTestString(const TestStringEvent &event) override {
            CHECK_EQ("42", event.str);
        }

        void onTestInt(const TestIntEvent &event) override {
            CHECK_EQ(42, event.value);
        }
    };

    TEST_CASE("Listener") {
        auto em = orion::EventManager::create();
        TestEventListener_1 tel_1(em);

        {
            TestEventListener_2 tel_2(em);

            TestStringEvent se = {"42"};
            em->emit(se);
            TestIntEvent ie = {42};
            em->emit(ie);
        }

        TestStringEvent se = {"42"};
        em->emit(se);
        TestIntEvent ie = {42};
        em->emit(ie);
    }
}