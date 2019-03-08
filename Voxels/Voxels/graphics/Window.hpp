//
//  Window.hpp
//  Voxels
//
//  Created by Aaron Hodel on 08.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>

#include "config/StaticConfig.hpp"

namespace graphics {
    
    typedef void (*renderFunc)();
    
    class Window {
    private:
        SDL_Window *window = nullptr;
        SDL_GLContext context;
        bool running = false;

        void initGL();
        void initContext();
        
    public:
        Window();
        
        void run();
    };
    
}

#endif /* Window_hpp */
