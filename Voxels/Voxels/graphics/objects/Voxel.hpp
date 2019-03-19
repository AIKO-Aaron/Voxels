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
#include "math/Physics.hpp"

enum voxelType{
    BLANK = 0,
    
};

namespace graphics {
    namespace objects {
        class Voxel : public Object {
        private:            
			physics::vec3 size;

        public:
            //type and color
            voxelType voxelType;
            
            Voxel(Shader *shader, enum::voxelType voxelType, float x, float y, float z, float w, float h, float d, Material m);
            
            void init(float x, float y, float z, float w, float h, float d, Material m);
            void move(physics::vec3 dxyz);

			std::vector<physics::hitboxData> getHitbox() override;
        };
        
    }
}

#endif /* Voxel_hpp */
