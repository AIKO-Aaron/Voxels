//
//  main.cpp
//  Voxels
//
//  Created by Aaron Hodel on 07.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "config/StaticConfig.hpp"
#include "graphics/Window.hpp"
#include "graphics/Shader.hpp"
#include "math/Physics.hpp"
#include "graphics/objects/Voxel.hpp"
#include "graphics/Chunk.hpp"

#include <vector>

std::vector<graphics::Chunk*> chunks;
graphics::Shader *shader;
// For the shaders
physics::vec3 playerPos, playerAngle;
float currentTime = 0;

void render(graphics::Window *window) {
	glClearColor(0, 0, 0, 1); // Clear background to black

    for (int i = 0; i < chunks.size(); i++) chunks[i]->render();
    
    shader->uniformf("time", currentTime);
    shader->uniformf("playerPos", playerPos);
    shader->uniformf("playerView", playerAngle);

    currentTime += 0.01;
    
    if(window->isKeyPressed(SDL_SCANCODE_D)) playerPos -= physics::createVec(0.1 * cos(playerAngle[1]), 0, 0.1 * sin(playerAngle[1]));
    if(window->isKeyPressed(SDL_SCANCODE_A)) playerPos += physics::createVec(0.1 * cos(playerAngle[1]), 0, 0.1 * sin(playerAngle[1]));
    if(window->isKeyPressed(SDL_SCANCODE_W)) playerPos -= physics::createVec(-0.1 * sin(playerAngle[1]), 0, 0.1 * cos(playerAngle[1]));
    if(window->isKeyPressed(SDL_SCANCODE_S)) playerPos += physics::createVec(-0.1 * sin(playerAngle[1]), 0, 0.1 * cos(playerAngle[1]));

    if(window->isKeyPressed(SDL_SCANCODE_SPACE)) playerPos -= physics::createVec(0, 0.1, 0);
    if(window->isKeyPressed(SDL_SCANCODE_LSHIFT)) playerPos += physics::createVec(0, 0.1, 0);
}

void handleEvent(SDL_Event e) {
    if(e.type == SDL_MOUSEMOTION) {
        playerAngle += physics::createVec(e.motion.yrel / 200.0f, -e.motion.xrel / 200.0f, 0);
    }
}

int main(int argc, char **args) {
    graphics::Window window = graphics::Window();
    
    //push a test voxel into a junk
    chunks.push_back(new graphics::Chunk(0,0));
    chunks[0]->voxels.push_back(new graphics::objects::Voxel(BLANK, 0, 0, 0, 1, 1, 1));
    chunks[0]->voxels.push_back(new graphics::objects::Voxel(BLANK, 1, 0, 0, 1, 1, 1));
    
    shader = graphics::loadFromFiles("./assets/shaders/shader.vert", "./assets/shaders/shader.frag");
    shader->bind();
    
	window.addEventFunc(handleEvent);
	window.addRenderFunc(render);
    window.run();
    return 0;
}
