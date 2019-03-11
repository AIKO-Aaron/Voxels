//
//  Window.cpp
//  Voxels
//
//  Created by Aaron Hodel on 08.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Window.hpp"

graphics::Window::Window() {
    initGL();
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    initContext();
}

graphics::Window::~Window() {
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	SDL_Quit();
}

void graphics::Window::run() {
    SDL_ShowWindow(window);
    running = true;

    SDL_Event e;
    while(running) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_WINDOWEVENT) {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
            }

			for (eventFunc dis : eventDispatchers) dis(e);
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
		for (renderFunc dis : renderDispatchers) dis();
        
        SDL_GL_SwapWindow(window);
    }
}

void graphics::Window::initGL() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    
#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // Load GL version 3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2); // .2
#else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // Load GL version 4
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); // .1
#endif

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // The core profile (Macs don't have more than that above GL version 2.1)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); // Enable accelerated graphics
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Enable double buffering (No flickering)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Set the forward compability flag (Not sure if needed, but macs seem to need it)
    
    // 8 bits per color channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
}

void graphics::Window::initContext() {
    context = SDL_GL_CreateContext(window);
    
    if(context == nullptr) {
        printf("[ERROR] Couldn't create GL context %d\n", glGetError());
        exit(1);
    }
    
    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        printf("[ERROR] Couldn't initialize GLEW\n");
        exit(1);
    }
    
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    
#ifdef DEBUG_GL
    GLuint err = glGetError();
    int i = 0;
    printf("[INFO] Loaded GL Version: %s\n", glGetString(GL_VERSION));
    printf("[INFO] Loaded GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    while((err = glGetError()) != GL_INVALID_VALUE) printf("\t[INFO] Available extension: %s\n", glGetStringi(GL_EXTENSIONS, i++));
#endif
}
