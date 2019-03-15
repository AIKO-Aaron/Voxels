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
        
        typedef struct{
            float x, y, z, h, w, d;
       }objectData;
        
        class Object {
        protected:
            GLuint vaoID;
            Material material = Material(physics::createVec(1, 1, 1, 1));
            Shader *shader;
            objectData objectData;
            
        public:
            Object(Shader *shader);
            virtual void render() = 0;
            
            inline void setShader(Shader *shader) { this->shader = shader; }
            inline const Shader* getShader() { return shader; }
        };
        
    }
}

#endif /* Object_hpp */
