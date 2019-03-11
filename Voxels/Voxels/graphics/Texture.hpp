//
//  Texture.hpp
//  Voxels
//
//  Created by Aaron Hodel on 11.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GL/glew.h>

#ifdef __APPLE__
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_opengl.h>
#  include <SDL2_image/SDL_image.h>
#else
#  include "SDL.h"
#  include "SDL_opengl.h"
#  include "SDL_image.h"
#endif

namespace graphics {
    
    class Texture {
    private:
        GLuint texID;
    public:
        Texture(const char *path);
        
        inline void bind(int location) { glActiveTexture(GL_TEXTURE0 + location); glBindTexture(GL_TEXTURE_2D, texID); }
    };

}


#endif /* Texture_hpp */
