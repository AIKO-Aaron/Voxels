//
//  Entity.cpp
//  Voxels
//
//  Created by Keanu Gleixner on 14.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Entity.hpp"

using namespace graphics::entities;

Entity::Entity(graphics::Shader *sh, float x, float y, float z, entityType e) : shader(sh) {
    init(x, y, z, e);
}

void Entity::init(float x, float y, float z, entityType e) {
    data.type = e;
    data.x = x;
    data.y = y;
    data.z = z;
    
    graphics::objects::Material m1 = graphics::objects::Material(physics::createVec(0, 1, 0, 1));
    switch (data.type) {
        case Player:
            data.voxels.push_back(new graphics::objects::Voxel(shader, BLANK, x, y, z, 0.5, 0.5, 0.5, m1));
            break;
            
        default:
            break;
    }
}

void Entity::update() {
    
}

void Entity::render() {
    for (size_t i = 0; i < data.voxels.size(); i++) {
        data.voxels[i]->render();
    }
}

void Entity::move(physics::vec3 dxyz) {
    for (size_t i = 0; i < data.voxels.size(); i++) {
        data.voxels[i]->move(dxyz);
    }
}
