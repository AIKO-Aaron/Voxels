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

#ifdef __APPLE__
#  include <SDL2/SDL.h>
#  include <SDL2_image/SDL_image.h>
#  include <SDL2/SDL_opengl.h>
#else
#  include "SDL.h"
#  include "SDL_opengl.h"
#  include "SDL_image.h"
#endif

#include <stdio.h>
#include <vector>

#include "config/StaticConfig.hpp"

namespace graphics {
    
    typedef void (*renderFunc)();
	typedef void(*eventFunc)(SDL_Event e);
    
    class Window {
    private:
        SDL_Window *window = nullptr;
        SDL_GLContext context;
        bool running = false;

		std::vector<eventFunc> eventDispatchers;
		std::vector<renderFunc> renderDispatchers;

        void initGL();
        void initContext();
        
    public:
        Window();
		~Window();

		inline void addRenderFunc(renderFunc f) { renderDispatchers.push_back(f); }
		inline void addEventFunc(eventFunc f) { eventDispatchers.push_back(f); }

        void run();
    };
    
}

#endif /* Window_hpp */
