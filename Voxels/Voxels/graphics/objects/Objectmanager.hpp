//
//  Objectmanager.hpp
//  Voxels
//
//  Created by Keanu Gleixner on 28.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Objectmanager_hpp
#define Objectmanager_hpp

#include <GL/glew.h>

#ifdef __APPLE__
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_opengl.h>
#else
#  include "SDL.h"
#  include "SDL_opengl.h"
#endif


#include <stdio.h>

#endif /* Objectmanager_hpp */

class Objectmanager{
protected:
    GLuint vaoID, vboID, iboID;
public:
  
    Objectmanager();
    ~Objectmanager();
    
};
