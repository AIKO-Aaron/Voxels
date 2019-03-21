//
//  Material.hpp
//  Voxels
//
//  Created by Aaron Hodel on 11.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include "../../math/Physics.hpp"
#include "../Texture.hpp"
#include "../Shader.hpp"

namespace graphics {
    namespace objects {
        
        class Material {
        private:
            bool isTextured = false;
            physics::vec4 color;
            graphics::Texture *texture = nullptr;

            graphics::Texture *ambientTexture = new graphics::Texture("assets/textures/cube/ambient.png");
            graphics::Texture *diffuseTexture = new graphics::Texture("assets/textures/cube/diffuse.png");
            graphics::Texture *specularTexture = new graphics::Texture("assets/textures/cube/specular.png");
            
        public:
            float shininess = 32.0f;

            Material(physics::vec4 color);
            Material(Texture *texture);
            
            void use(Shader *shader);

        };
    
    }
}

#endif /* Material_hpp */
