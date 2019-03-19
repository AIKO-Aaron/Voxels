//
//  Material.cpp
//  Voxels
//
//  Created by Aaron Hodel on 12.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Material.hpp"

using namespace graphics::objects;

Material::Material(physics::vec4 col) : color(col) {
    isTextured = false;
}

Material::Material(graphics::Texture *tex) : texture(tex) {
    isTextured = true;
}

void Material::use(graphics::Shader *shader) {
    shader->uniformi("isTextured", isTextured ? 1 : 0);
    if(isTextured) {
        shader->uniformf("tex", 0);
        texture->bind(GL_TEXTURE0);
    } else {
        shader->uniformf("color", color);
    }
}
