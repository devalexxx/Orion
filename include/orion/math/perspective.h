//
// Created by Alex on 15/12/2023.
//

#ifndef ORION_PERSPECTIVE_H
#define ORION_PERSPECTIVE_H

#include "Matrix.h"

namespace orion {

    Matrix<4, 4, float> perspective(float fov, float aspect, float z_near, float z_far);

}

#endif //ORION_PERSPECTIVE_H
