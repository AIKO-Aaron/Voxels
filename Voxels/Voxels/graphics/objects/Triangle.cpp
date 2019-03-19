//
//  Triangle.cpp
//  Voxels
//
//  Created by Aaron Hodel on 13.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Triangle.hpp"

using namespace graphics::objects;

Triangle::Triangle(graphics::Shader *shader, physics::vec3 p1, physics::vec3 p2, physics::vec3 p3, Material mat) : Object(shader, 3) {
    material = mat;
    
    vertexData *verticies = new vertexData[3];
    
    verticies[0] = { p1[0], p1[1], p1[2], 0, 0 };
    verticies[1] = { p2[0], p2[1], p2[2], 1, 0 };
    verticies[2] = { p3[0], p3[1], p3[2], 1, 1 };

    GLubyte *indicies = new GLubyte[3] {
        0, 1, 2,
    };
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData) * 3, verticies, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexData), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(vertexData), (void*)(3 * sizeof(GLfloat)));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 3, indicies, GL_STATIC_DRAW);
}