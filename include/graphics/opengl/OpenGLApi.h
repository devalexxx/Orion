//
// Created by Alex on 26/12/2023.
//

#ifndef ORION_OPENGLAPI_H
#define ORION_OPENGLAPI_H

namespace orion {

    class OpenGLApi {
    public:
        static bool is_loaded;

        static void load();
    };

} // orion

#endif //ORION_OPENGLAPI_H
