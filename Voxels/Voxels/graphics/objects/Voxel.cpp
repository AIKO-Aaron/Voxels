//
//  Voxel.cpp
//  Voxels
//
//  Created by Aaron Hodel on 11.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Voxel.hpp"

using namespace graphics::objects;

Voxel::Voxel() : voxelType(BLANK) {
    init(0, 0, 0, 1, 1, 1);
}

Voxel::Voxel(enum::voxelType voxelType) : voxelType(voxelType){
    init(0, 0, 0, 1, 1, 1);
}

Voxel::Voxel(enum::voxelType voxelType, float x, float y, float z, float w, float h, float d) : voxelType(voxelType){
    init(x, y, z, w, h, d);
}

void Voxel::init(float x, float y, float z, float w, float h, float d) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    
    GLuint iboID;
    glGenBuffers(1, &iboID);
    
    texture = new graphics::Texture("assets/textures/cube/water.png");
    
    vertexData *verticies = new vertexData[24];
    
    verticies[0] = { x, y, z, 0, 0 };
    verticies[1] = { x + w, y, z, 1, 0 };
    verticies[2] = { x + w, y + h, z, 1, 1 };
    verticies[3] = { x, y + h, z, 0, 1 };
    
    verticies[4] = { x, y, z + d, 0, 0 };
    verticies[5] = { x, y + h, z + d, 0, 1 };
    verticies[6] = { x + w, y + h, z + d, 1, 1 };
    verticies[7] = { x + w, y, z + d, 1, 0 };
    
    verticies[8]  = { x, y, z, 0, 0 };
    verticies[9]  = { x, y + h, z, 0, 1 };
    verticies[10] = { x, y + h, z + d, 1, 1 };
    verticies[11] = { x, y, z + d, 1, 0 };
    
    verticies[12] = { x + w, y, z, 0, 0 };
    verticies[13] = { x + w, y, z + d, 0, 1 };
    verticies[14] = { x + w, y + h, z + d, 1, 1 };
    verticies[15] = { x + w, y + h, z, 1, 0 };
    
    verticies[16]  = { x, y + h, z, 0, 0 };
    verticies[17]  = { x + w, y + h, z, 0, 1 };
    verticies[18] = { x + w, y + h, z + d, 1, 1 };
    verticies[19] = { x, y + h, z + d, 1, 0 };
    
    verticies[20] = { x, y, z, 0, 0 };
    verticies[21] = { x, y, z + d, 0, 1 };
    verticies[22] = { x + w, y, z + d, 1, 1 };
    verticies[23] = { x + w, y, z, 1, 0 };
    
    GLubyte *indicies = new GLubyte[36] {
        0, 1, 2,
        2, 3, 0,
        
        4, 5, 6,
        6, 7, 4,
        
        8, 9, 10,
        10, 11, 8,
        
        12, 13, 14,
        14, 15, 12,
        
        16, 17, 18,
        18, 19, 16,
        
        20, 21, 22,
        22, 23, 20
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
    texture->bind(GL_TEXTURE0);
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);
}
