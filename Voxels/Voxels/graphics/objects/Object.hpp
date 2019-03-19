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
#include "../Shader.hpp"
#include "../../math/Physics.hpp"

namespace graphics {
    namespace objects {
        
        typedef struct {
            float x, y, z; // Position
            float u, v; // UV in the texture
            float nx, ny, nz; // Normal vector
        } vertexData;
        
#define POS_OFFSET ((void*) (sizeof(float) * 0))
#define UV_OFFSET ((void*) (sizeof(float) * 3))
#define NORMAL_OFFSET ((void*) (sizeof(float) * 5))

        typedef struct{
			physics::vec3 size;
			physics::vec3 rotation;
       } objectData;
        
        class Object : public physics::Element {
		private:
			int vertexCount;

        protected:
            GLuint vaoID, vboID, iboID;
            Material material = Material(physics::createVec(1, 1, 1, 1));
            Shader *shader;
            objectData data;
            
        public:
            Object(Shader *shader, int vertexCount);
            void render();
            
			inline void move(physics::vec3 dxyz) { position += dxyz; }
			inline void rotate(physics::vec3 dxyz) { data.rotation += dxyz; }

			inline objectData getData() { return data; }

            inline void setShader(Shader *shader) { this->shader = shader; }
            inline const Shader* getShader() { return shader; }
        };
        
    }
}

#endif /* Object_hpp */
