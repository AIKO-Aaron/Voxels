//
//  Voxel.hpp
//  Voxels
//
//  Created by Aaron Hodel on 11.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Voxel_hpp
#define Voxel_hpp

#include "../../math/Physics.hpp"
#include "Object.hpp"
#include "../Texture.hpp"

enum voxelType{
    BLANK = 0,
    
};

namespace graphics {
    namespace objects {
        class Voxel : public Object {
        private:
            
        public:
            //type and color
            voxelType voxelType;
            
            Voxel(Shader *shader, enum::voxelType voxelType, float x, float y, float z, float w, float h, float d, Material m);
            //Voxel(enum::voxelType voxelType);
            //Voxel(enum::voxelType voxelType, float x, float y, float z, float w, float h, float d, Material m);
            void init(float x, float y, float z, float w, float h, float d, Material m);
            void render();
        };
        
    }
}

#endif /* Voxel_hpp */
