//
// Created by Alex on 21/11/2023.
//

#include "doctest/doctest.h"

#include <thread>

//#include "core.h"
//
//TEST_SUITE("Window") {
//
//    TEST_CASE("Window event") {
//
//        class IEL : orion::KeyEventListener { ;
//        public:
//            explicit IEL(const std::shared_ptr<orion::EventManager>& event_manager) : orion::KeyEventListener(event_manager) {}
//
//            void onPressed(const orion::Input::KeyEvent &event) override {
//                if (event.key == orion::Input::Key::ESCAPE)
//                    if(!event.window.expired())
//                        event.window.lock()->close();
//            }
//        };
//
//        class WEL : orion::WindowEventListener { ;
//        public:
//            explicit WEL(const std::shared_ptr<orion::EventManager>& event_manager) : orion::WindowEventListener(event_manager) {}
//
//            void onPositionChange(const orion::WindowPositionEvent &event) override {
//                std::cout << "last : " << event.last.x << ", current : " << event.current.x << "\n";
//            }
//        };
//
//        auto em = std::make_shared<orion::EventManager>();
//        auto win = orion::Window::create("Event test");
//        win->setEventManager(em);
//        WEL wel(em);
//        IEL iel(em);
//
//        using namespace std::chrono_literals;
//
//        std::thread t([&]() {
//            std::this_thread::sleep_for(10s);
//            orion::Input::KeyEvent e {
//                {win},
//                orion::Input::Key::ESCAPE,
//                0,
//                true,
//                false,
//                false,
//                false,
//                false,
//                false,
//                false,
//                false,
//            };
//            em->emit(e);
//        });
//
//        win->run();
//
//        t.join();
//    }
//
//}