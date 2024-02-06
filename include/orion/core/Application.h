//
// Created by Alex on 22/01/2024.
//

#ifndef ORION_APPLICATION_H
#define ORION_APPLICATION_H

#include "orion/core/type.h"

namespace orion {

    class Application {
    public:
        explicit Application(String name);

        i32 run(i32 argc, i8* argv[]);
    private:
        String m_name;
    };

} // orion

#endif //ORION_APPLICATION_H
