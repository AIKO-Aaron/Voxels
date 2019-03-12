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


#define PI 3.14
#define MOVESPEED 0.3

std::vector<graphics::Chunk*> chunks;
graphics::Shader *shader;
// For the shaders
physics::vec3 playerPos, playerAngle, moveVec;
float currentTime = 0;

void render(graphics::Window *window) {
	glClearColor(0, 0, 0, 1); // Clear background to black

    for (int i = 0; i < chunks.size(); i++) chunks[i]->render();
    
    shader->uniformf("time", currentTime);
    shader->uniformf("playerPos", playerPos);
    shader->uniformf("playerView", playerAngle);

    currentTime += 0.01;
    
    if(window->isKeyPressed(SDL_SCANCODE_D)) moveVec -= physics::createVec(0, 0, 0.025);
    else {
        if (moveVec[2] < 0){
            moveVec += physics::createVec(0, 0, 0.025);
            if (moveVec[2] > 0) moveVec[2] = 0;
        }
    }
    if(window->isKeyPressed(SDL_SCANCODE_A)) moveVec += physics::createVec(0, 0, 0.025);
    else {
        if (moveVec[2] > 0){
            moveVec -= physics::createVec(0, 0, 0.025);
            if (moveVec[2] < 0) moveVec[2] = 0;
        }
    }
    if(window->isKeyPressed(SDL_SCANCODE_W)) moveVec += physics::createVec(0.025, 0, 0);
    else {
        if (moveVec[0] > 0){
            moveVec -= physics::createVec(0.025, 0, 0);
            if (moveVec[0] < 0) moveVec[0] = 0;
        }
    }
    if(window->isKeyPressed(SDL_SCANCODE_S)) moveVec -= physics::createVec(0.025, 0, 0);
    else {
        if (moveVec[0] < 0){
            moveVec += physics::createVec(0.025, 0, 0);
            if (moveVec[0] > 0) moveVec[0] = 0;
        }
    }
    if(window->isKeyPressed(SDL_SCANCODE_SPACE)) moveVec -= physics::createVec(0, 0.025, 0);
    else {
        if (moveVec[1] < 0){
            moveVec += physics::createVec(0, 0.025, 0);
            if (moveVec[1] > 0) moveVec[1] = 0;
        }
    }
    if(window->isKeyPressed(SDL_SCANCODE_LSHIFT)) moveVec += physics::createVec(0, 0.025, 0);
    else {
        if (moveVec[1] > 0){
            moveVec -= physics::createVec(0, 0.025, 0);
            if (moveVec[1] < 0) moveVec[1] = 0;
        }
    }
    
    //limit the direction vector to length 1
    float len = sqrt(pow(moveVec[0],2) + pow(moveVec[1],2) + pow(moveVec[2],2));
    if (len > 1) moveVec /= len;
        
    playerPos += (physics::createVec(-0.1 * sin(playerAngle[1]), 0, 0.1 * cos(playerAngle[1])) * -moveVec[0]) * MOVESPEED;
    playerPos += (physics::createVec(0.1 * cos(playerAngle[1]), 0, 0.1 * sin(playerAngle[1])) * moveVec[2]) * MOVESPEED;
    playerPos += (physics::createVec(0.0, 0.1, 0.0) * moveVec[1]) * MOVESPEED;
}

void handleEvent(SDL_Event e) {
    if(e.type == SDL_MOUSEMOTION) {
        playerAngle += physics::createVec(e.motion.yrel / 200.0f, -e.motion.xrel / 200.0f, 0);
        if (playerAngle[0] < -PI/2) playerAngle[0] = -PI/2;
        if (playerAngle[0] > PI/2) playerAngle[0] = PI/2;
    }
}

int main(int argc, char **args) {
    graphics::Window window = graphics::Window();
    
    shader = graphics::loadFromFiles("./assets/shaders/shader.vert", "./assets/shaders/shader.frag");
    shader->bind();

    //push a test voxel into a junk
    chunks.push_back(new graphics::Chunk(0,0));
    graphics::objects::Material m1 = graphics::objects::Material(physics::createVec(0, 0, 1, 1));
    graphics::objects::Material m2 = graphics::objects::Material(physics::createVec(1, 1, 1, 1));
    chunks[0]->voxels.push_back(new graphics::objects::Voxel(shader, BLANK, 0, 0, 0, 1, 1, 1, m1));
    chunks[0]->voxels.push_back(new graphics::objects::Voxel(shader, BLANK, 1, 0, 0, 1, 1, 1, m2));
    
	window.addEventFunc(handleEvent);
	window.addRenderFunc(render);
    window.run();
    return 0;
}
