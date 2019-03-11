//
//  Voxel.hpp
//  Voxels
//
//  Created by Aaron Hodel on 11.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Voxel_hpp
#define Voxel_hpp

#include "Object.hpp"

namespace graphics {
    namespace objects {
        
        class Voxel : public Object {
        private:
            
        public:
            Voxel();
            void render();
        };
        
    }
}

#endif /* Voxel_hpp */
