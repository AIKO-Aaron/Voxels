//
//  Entity.cpp
//  Voxels
//
//  Created by Keanu Gleixner on 14.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Entity.hpp"

using namespace graphics::entities;

Entity::Entity(Shader *shader, float x, float y, float z, enum::entityType e) : shader(shader){
    init(x, y, z, e);
}

void Entity::init(float x, float y, float z, enum::entityType e){
    entityData.entityType = e;
    entityData.x = x;
    entityData.y = y;
    entityData.z = z;
    
    graphics::objects::Material m1 = graphics::objects::Material(physics::createVec(0, 1, 0, 1));
    switch (entityData.entityType) {
        case Player:
            entityData.voxels.push_back(new graphics::objects::Voxel(shader, BLANK, x, y, z, 0.5, 0.5, 0.5, m1));
            break;
            
        default:
            break;
    }
}

void Entity::update(){
    
}

void Entity::render(){
    for (int i = 0; i < entityData.voxels.size(); i++) {
        entityData.voxels[i]->render();
    }
}

void Entity::move(physics::vec3 dxyz){
    for (int i = 0; i < entityData.voxels.size(); i++) {
        entityData.voxels[i]->move(dxyz);
    }
}
