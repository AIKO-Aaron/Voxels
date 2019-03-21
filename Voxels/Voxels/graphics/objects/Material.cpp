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
    
    // Temporary do this:
    ambientTexture = tex;
    diffuseTexture = tex;
    specularTexture = tex;
}

void Material::use(graphics::Shader *shader) {
    shader->uniformi("mat.isTextured", isTextured ? 1 : 0);
    shader->uniformf("mat.shininess", shininess);
    if(isTextured) {
        shader->uniformf("mat.tex", 0);
        texture->bind(GL_TEXTURE0);
        
        shader->uniformf("mat.ambientTex", 1);
        ambientTexture->bind(GL_TEXTURE1);
        shader->uniformf("mat.diffuseTex", 2);
        diffuseTexture->bind(GL_TEXTURE2);
        shader->uniformf("mat.specularTex", 3);
        specularTexture->bind(GL_TEXTURE3);
    } else {
        shader->uniformf("mat.color", color);
    }
}
