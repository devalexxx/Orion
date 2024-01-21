//
// Created by Alex on 20/11/2023.
//

#include "doctest/doctest.h"

#include "orion/core.h"

#include <vector>
#include <thread>

TEST_SUITE("Event") {

    struct TestThreadEvent {
        std::thread::id id;
    };

    class TestThreadEventListener : public orion::EventListener {
    public:
        int call_count = 0;

        explicit TestThreadEventListener(const std::shared_ptr<orion::EventManager>& e_manager) : orion::EventListener(e_manager) {
            bind(&TestThreadEventListener::onTestThread);
        }

        void onTestThread(const TestThreadEvent& event) {
            call_count++;
            CHECK_EQ(event.id, std::this_thread::get_id());
        };
    };

    TEST_CASE("Thread safety event manager") {
        auto em = orion::EventManager::create();

        size_t thread_count     = std::thread::hardware_concurrency();
        size_t emit_per_thread  = 50;

        TestThreadEventListener tel(em);

        std::vector<std::thread> pool;
        pool.reserve(thread_count);

        for (int i = 0; i < thread_count; ++i) {
            pool.emplace_back([&]() {
                for (int j = 0; j < emit_per_thread; ++j) {
                    TestThreadEvent event = {std::this_thread::get_id()};
                    em->emit(event);
                }
            });
        }

        for (int i = 0; i < thread_count; ++i) {
            pool[i].join();
        }

        CHECK_EQ(tel.call_count, thread_count * emit_per_thread);
    }
}