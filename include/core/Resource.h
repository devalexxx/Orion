//
// Created by Alex on 05/01/2024.
//

#ifndef ORION_RESOURCE_H
#define ORION_RESOURCE_H

#include "type.h"



namespace orion::resource {
    static Path WORKING_DIRECTORY = "./resource";

    Path of(Ref<String> filename);

    namespace texture {
        static Path DIRECTORY = WORKING_DIRECTORY / "texture";

        Path of(Ref<String> filename);
    }

    namespace shader {
        static Path DIRECTORY = WORKING_DIRECTORY / "shader";

        Path of(Ref<String> filename);
    }

}

// orion

#endif //ORION_RESOURCE_H
