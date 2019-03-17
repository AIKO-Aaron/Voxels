//
//  Object.cpp
//  Voxels
//
//  Created by Aaron Hodel on 11.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Object.hpp"

using namespace graphics::objects;

Object::Object(graphics::Shader *sh, int vc) : shader(sh), vertexCount(vc) {
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

	glGenBuffers(1, &vboID);
	glGenBuffers(1, &iboID);
}

void Object::render() {
	shader->uniformf("vertPos", position);
	shader->uniformf("vertRot", data.rotation);
	material.use(shader);
	glBindVertexArray(vaoID);
	glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_BYTE, 0);
}