//
// Created by Alex on 22/01/2024.
//

#include "orion/core/Application.h"

namespace orion {

    Application::Application(String name) : m_name (std::move(name)) {}

    i32 Application::run(i32 argc, i8* argv[]) {
        return EXIT_SUCCESS;
    }

} // orion