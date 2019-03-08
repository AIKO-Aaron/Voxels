//
//  Window.cpp
//  Voxels
//
//  Created by Aaron Hodel on 08.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Window.hpp"

graphics::Window::Window() {
    SDL_Window *window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    SDL_ShowWindow(window);
    bool running = true;
    SDL_Event e;
    while(running) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_WINDOWEVENT) {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
            }
        }
    }
    SDL_DestroyWindow(window);
}
