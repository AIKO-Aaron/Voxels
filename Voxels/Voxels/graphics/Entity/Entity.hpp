//
//  Entity.hpp
//  Voxels
//
//  Created by Keanu Gleixner on 14.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp
#include "../objects/Object.hpp"
#include "../objects/Voxel.hpp"
#include <vector>

#include <stdio.h>

#define GRAVITY 0.002

enum entityType {
    Player = 0
};

namespace graphics {
    namespace entities {

        typedef struct {
            float x, y, z;
            entityType type;
            std::vector<objects::Voxel*> voxels;
        } entityData;
        
        class Entity {
        private:
            
        public:
            entityData data;
            Shader *shader;

            
            Entity(Shader *shader, float x, float y, float z, entityType e);
            void init(float x, float y, float z, entityType e);
            void render();
            void update();
            void move(physics::vec3 dxyz);
        };
    }
}

#endif /* Entity_hpp */
