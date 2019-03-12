//
//  Object.hpp
//  Voxels
//
//  Created by Aaron Hodel on 11.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <GL/glew.h>

#ifdef __APPLE__
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_opengl.h>
#else
#  include "SDL.h"
#  include "SDL_opengl.h"
#endif

#include "Material.hpp"
#include "Shader.hpp"

namespace graphics {
    namespace objects {
        
        typedef struct {
            float x, y, z;
            float u, v;
        } vertexData;
        
        class Object {
        protected:
            GLuint vaoID;
            Material material = Material(physics::createVec(1, 1, 1, 1));
            
        public:
            Object();
            virtual void render() = 0;
            
        };
        
    }
}

#endif /* Object_hpp */
