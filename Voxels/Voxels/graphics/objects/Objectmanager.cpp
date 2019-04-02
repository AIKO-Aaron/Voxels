//
//  Objectmanager.cpp
//  Voxels
//
//  Created by Keanu Gleixner on 28.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Objectmanager.hpp"

Objectmanager::Objectmanager(){
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    
    glGenBuffers(1, &vboID);
    glGenBuffers(1, &iboID);
}
