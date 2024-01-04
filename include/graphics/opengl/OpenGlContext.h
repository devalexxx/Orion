//
// Created by Alex on 04/01/2024.
//

#ifndef ORION_OPENGLCONTEXT_H
#define ORION_OPENGLCONTEXT_H

#include "GLFW/glfw3.h"

namespace orion {

    class OpenGlContext {
    public:
        using Context = GLFWwindow*;

        static Context get_current();

        static void set_current(Context context);

        static void on_any_destroy(Context context);
        static bool is_any_current();
    };

} // orion

#endif //ORION_OPENGLCONTEXT_H
