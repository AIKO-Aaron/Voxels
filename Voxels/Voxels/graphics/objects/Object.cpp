//
//  Object.cpp
//  Voxels
//
//  Created by Aaron Hodel on 11.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Object.hpp"

graphics::objects::Object::Object(Shader *shader) : shader(shader) {
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
}
