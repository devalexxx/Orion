| Platform  | Build Status                                                                                                                                                                   |
|-----------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Windows   | [![Windows build](https://github.com/alspin8/Orion/actions/workflows/build-windows.yml/badge.svg)](https://github.com/alspin8/Orion/actions/workflows/build-windows.yml)       |
| Ubuntu    | [![Ubuntu build](https://github.com/alspin8/Orion/actions/workflows/build-ubuntu.yml/badge.svg)](https://github.com/alspin8/Orion/actions/workflows/build-ubuntu.yml)          |
| Macos ARM | [![Macos arm build](https://github.com/alspin8/Orion/actions/workflows/build-macos-arm.yml/badge.svg)](https://github.com/alspin8/Orion/actions/workflows/build-macos-arm.yml) |
| Macos     | [![Macos build](https://github.com/alspin8/Orion/actions/workflows/build-macos.yml/badge.svg)](https://github.com/alspin8/Orion/actions/workflows/build-macos.yml)             |


## Installation

### Install xmake
https://xmake.io/#/guide/installation

### From GitHub

#### Clone repository
````bash
git clone https://github.com/alspin8/Orion.git
````

#### Configure
````bash
xmake f --mode=<debug|release> --shared=<y|n> --unittest=<y|n> --nogpu=<y|n> --sandbox=<y|n>
````

#### Build
````bash
xmake
````

### From xrepo

#### Add repository
````bash
xrepo add-repo orion-repo https://github.com/alspin8/xmake-repo.git main
````

#### Install package (version match with tags name)
````bash
xrepo install orion <version>
````

## Usage

Create a simple program that draw a triangle.

#### xmake.lua

````lua
add_rules("mode.debug", "mode.release")

set_language("c++23")

add_repositories("orion-repo https://github.com/devalexxx/xmake-repo.git")

add_requires("orion", { config = { debug = is_mode("debug") } })

target("orion_test")
    set_kind("binary")
    add_files("src/*.cpp")

    add_packages("orion")
    add_rules("@orion/resource")
````

#### main.cpp

````c++
#include <orion/graphics.h>

int main(int argc, char** argv)
{
    auto event_manager = orion::EventManager::create();
    auto window        = orion::Window::create("Test");
    
    window->set_event_manager(event_manager);
    
    event_manager->subscribe<orion::Input::KeyEvent>([](const auto& event)
    {
        if (event.key == orion::Input::Key::ESCAPE && event.pressed)
        {
            event.window.lock()->close();    
        }
    });
    
    window->get_view().transalte(orion::Vector3f(0.f, 0.f, 5.f));
    window->get_view().look_at  (orion::Vector3f(0.f, 0.f, 0.f));
    
    orion::Shape shape(orion::Primitive::TRIANGLE);
    
    while(!window->is_close())
    {
        window->clear(orion::ClearMask::COLOR | orion::ClearMask::DEPTH);
        window->draw(shape);
        window->display();
    }
    
    return EXIT_SUCCESS;
}

````

## Credits
* [xmake](https://xmake.io/#/)
* [glfw](https://github.com/glfw/glfw.github.io)
* [glew](https://github.com/nigels-com/glew)
* [doctest](https://github.com/doctest/doctest)
* [stb](https://github.com/nothings/stb)
* [fmt](https://github.com/fmtlib/fmt)

