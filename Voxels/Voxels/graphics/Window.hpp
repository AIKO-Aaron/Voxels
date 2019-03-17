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
#include <time.h>
#include <chrono>
#include <thread>
#include <string>

#include "config/StaticConfig.hpp"

namespace graphics {
    
    class Window;
    typedef void (*renderFunc)(Window *window);
	typedef void(*eventFunc)(SDL_Event e);
    
    class Window {
    private:
        SDL_Window *window = nullptr;
        SDL_GLContext context;
        bool running = false;
        
        const uint8_t *keys;
        
        int fps = 0, lastFPS = 0;
        bool titleUpdate = false;
        friend uint32_t second_callback(uint32_t, void *params);
        
		std::vector<eventFunc> eventDispatchers;
		std::vector<renderFunc> renderDispatchers;

        void initGL();
        void initContext();
        
    public:
        Window();
		~Window();

		inline void addRenderFunc(renderFunc f) { renderDispatchers.push_back(f); }
		inline void addEventFunc(eventFunc f) { eventDispatchers.push_back(f); }
        inline bool isKeyPressed(int index) { return keys[index] > 0; }

        void run();
    };
    
}

#endif /* Window_hpp */
