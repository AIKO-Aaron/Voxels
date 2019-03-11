//
//  Voxel.cpp
//  Voxels
//
//  Created by Aaron Hodel on 11.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Voxel.hpp"

using namespace graphics::objects;

Voxel::Voxel() {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    
    GLuint iboID;
    glGenBuffers(1, &iboID);
    
    vertexData *verticies = new vertexData[24];
    
    verticies[0] = { 0, 0, 0, 0, 0 };
    verticies[1] = { 1, 0, 0, 1, 0 };
    verticies[2] = { 1, 1, 0, 1, 1 };
    verticies[3] = { 0, 1, 0, 0, 1 };
    
    verticies[4] = { 0, 0, -1, 0, 0 };
    verticies[5] = { 0, 1, -1, 0, 1 };
    verticies[6] = { 1, 1, -1, 1, 1 };
    verticies[7] = { 1, 0, -1, 1, 0 };
    
    GLubyte *indicies = new GLubyte[36] {
        0, 1, 2,
        2, 3, 0,
        
        4, 5, 6,
        6, 7, 4
    };
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData) * 24, verticies, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexData), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(vertexData), (void*)(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, indicies, GL_STATIC_DRAW);
}

void Voxel::render() {
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, 0);
}
