//
//  Triangle.hpp
//  Voxels
//
//  Created by Aaron Hodel on 13.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include "Object.hpp"

namespace graphics {
    namespace objects {
        
        class Triangle : public Object {
        private:
            
        public:
            Triangle(Shader *shader, physics::vec3 p1, physics::vec3 p2, physics::vec3 p3, Material m);

			inline std::vector<physics::hitboxData> getHitbox() override { return std::vector<physics::hitboxData>(); } // No hitbox (triangle is only 2D)
        };
        
    }
}

#endif /* Triangle_hpp */
