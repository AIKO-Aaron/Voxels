//
//  Material.cpp
//  Voxels
//
//  Created by Aaron Hodel on 12.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Material.hpp"

using namespace graphics::objects;

Material::Material(physics::vec4 color) : color(color) {
    isTextured = false;
}

Material::Material(Texture *texture) : texture(texture) {
    isTextured = true;
}

void Material::use(Shader *shader) {
    shader->uniformi("isTextured", isTextured ? 1 : 0);
    if(isTextured) {
        shader->uniformf("tex", 0);
        texture->bind(GL_TEXTURE0);
    } else {
        shader->uniformf("color", color);
    }
}
