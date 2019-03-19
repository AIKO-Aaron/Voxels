//
//  Voxel.cpp
//  Voxels
//
//  Created by Aaron Hodel on 11.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Voxel.hpp"

using namespace graphics::objects;

Voxel::Voxel(graphics::Shader *shader, enum::voxelType voxelType, float x, float y, float z, float w, float h, float d, Material m) : Object(shader, 36), voxelType(voxelType) {
    init(x, y, z, w, h, d, m);
}


void Voxel::init(float x, float y, float z, float w, float h, float d, Material mat) {    

    material = mat;
    
    vertexData *verticies = new vertexData[24];
    
	float w2 = w / 2.0f;
	float h2 = h / 2.0f;
	float d2 = d / 2.0f;

	size = physics::createVec(w, h, d);
	position = physics::createVec(x, y, z);

	verticies[0]  = { -w2, -h2, -d2, 0, 0 };
	verticies[1]  = {  w2, -h2, -d2, 1, 0 };
	verticies[2]  = {  w2,  h2, -d2, 1, 1 };
	verticies[3]  = { -w2,  h2, -d2, 0, 1 };

	verticies[4]  = { -w2, -h2,  d2, 0, 0 };
	verticies[5]  = { -w2,  h2,  d2, 0, 1 };
	verticies[6]  = {  w2,  h2,  d2, 1, 1 };
	verticies[7]  = {  w2, -h2,  d2, 1, 0 };

	verticies[8]  = { -w2, -h2, -d2, 0, 0 };
	verticies[9]  = { -w2,  h2, -d2, 0, 1 };
	verticies[10] = { -w2,  h2,  d2, 1, 1 };
	verticies[11] = { -w2, -h2,  d2, 1, 0 };

	verticies[12] = {  w2, -h2, -d2, 0, 0 };
	verticies[13] = {  w2, -h2,  d2, 0, 1 };
	verticies[14] = {  w2,  h2,  d2, 1, 1 };
	verticies[15] = {  w2,  h2, -d2, 1, 0 };

	verticies[16] = { -w2,  h2, -d2, 0, 0 };
	verticies[17] = {  w2,  h2, -d2, 0, 1 };
	verticies[18] = {  w2,  h2,  d2, 1, 1 };
	verticies[19] = { -w2,  h2,  d2, 1, 0 };

	verticies[20] = { -w2, -h2, -d2, 0, 0 };
	verticies[21] = { -w2, -h2,  d2, 0, 1 };
	verticies[22] = {  w2, -h2,  d2, 1, 1 };
	verticies[23] = {  w2, -h2, -d2, 1, 0 };
    
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

void Voxel::move(physics::vec3 dxyz){
    position += dxyz;
    shader->uniformf("globalPosition", position);
    
}

    
std::vector<physics::hitboxData> Voxel::getHitbox() {
	std::vector<physics::hitboxData> hitbox;

	hitbox.push_back({ position[0], position[1], position[2], size[0], size[1], size[2] });

	return hitbox;
}

