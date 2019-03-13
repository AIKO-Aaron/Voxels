//
//  PlaygroundKeanu.h
//  Voxels
//
//  Created by Aaron Hodel on 13.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef PlaygroundKeanu_hpp
#define PlaygroundKeanu_hpp

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
physics::vec3 playerPos = physics::createVec(0, -2, 0), playerAngle, moveVec;
float currentTime = 0;

/**
 Gets called once, after the window was init & before rendering starts
 Init all your stuff here
 */
static void initPlayground() {
    shader = graphics::loadFromFiles("./assets/shaders/shader.vert", "./assets/shaders/shader.frag");
    shader->bind();
    
    //push a test voxel into a junk
    chunks.push_back(new graphics::Chunk(0,0));
    graphics::objects::Material m1 = graphics::objects::Material(physics::createVec(0, 0, 1, 1));
    graphics::objects::Material m2 = graphics::objects::Material(new graphics::Texture("assets/textures/cube/water.png"));
    for(int i = 0; i < 100; i++) {
        int x = i % 10;
        int z = i / 10;
        chunks[0]->voxels.push_back(new graphics::objects::Voxel(shader, BLANK, x, 0, z, 1, 1, 1, (x + z) % 2 == 0 ? m1 : m2));
    }
}

/**
 Function that renders everything, also resppnsible to update everything
 */
static void render(graphics::Window *window) {
    glClearColor(0, 0, 0, 1); // Clear background to black
    
    for (int i = 0; i < chunks.size(); i++) chunks[i]->render();
    
    shader->uniformf("time", currentTime);
    shader->uniformf("playerPos", playerPos);
    shader->uniformf("playerView", playerAngle);
    
    currentTime += 0.01;
    
    if(window->isKeyPressed(SDL_SCANCODE_D)) moveVec -= physics::createVec(0, 0, ACCELERATION);
    else {
        if (moveVec[2] < 0) {
            moveVec += physics::createVec(0, 0, ACCELERATION);
            if (moveVec[2] > 0) moveVec[2] = 0;
        }
    }
    if(window->isKeyPressed(SDL_SCANCODE_A)) moveVec += physics::createVec(0, 0, ACCELERATION);
    else {
        if (moveVec[2] > 0) {
            moveVec -= physics::createVec(0, 0, ACCELERATION);
            if (moveVec[2] < 0) moveVec[2] = 0;
        }
    }
    if(window->isKeyPressed(SDL_SCANCODE_W)) moveVec += physics::createVec(ACCELERATION, 0, 0);
    else {
        if (moveVec[0] > 0) {
            moveVec -= physics::createVec(ACCELERATION, 0, 0);
            if (moveVec[0] < 0) moveVec[0] = 0;
        }
    }
    if(window->isKeyPressed(SDL_SCANCODE_S)) moveVec -= physics::createVec(ACCELERATION, 0, 0);
    else {
        if (moveVec[0] < 0) {
            moveVec += physics::createVec(ACCELERATION, 0, 0);
            if (moveVec[0] > 0) moveVec[0] = 0;
        }
    }
    if(window->isKeyPressed(SDL_SCANCODE_SPACE)) moveVec -= physics::createVec(0, ACCELERATION, 0);
    else {
        if (moveVec[1] < 0) {
            moveVec += physics::createVec(0, ACCELERATION, 0);
            if (moveVec[1] > 0) moveVec[1] = 0;
        }
    }
    if(window->isKeyPressed(SDL_SCANCODE_LSHIFT)) moveVec += physics::createVec(0, ACCELERATION, 0);
    else {
        if (moveVec[1] > 0) {
            moveVec -= physics::createVec(0, ACCELERATION, 0);
            if (moveVec[1] < 0) moveVec[1] = 0;
        }
    }
    
    //limit the direction vector to length 1
    float len = moveVec.len();
    if (len > 1) moveVec /= len;
    
    playerPos += (physics::createVec(-0.1 * sin(playerAngle[1]), 0, 0.1 * cos(playerAngle[1])) * -moveVec[0]) * MOVESPEED;
    playerPos += (physics::createVec(0.1 * cos(playerAngle[1]), 0, 0.1 * sin(playerAngle[1])) * moveVec[2]) * MOVESPEED;
    playerPos += (physics::createVec(0.0, 0.1, 0.0) * moveVec[1]) * MOVESPEED;
}

/**
 If an event happens, you can handle it here
 */
static void handleEvent(SDL_Event e) {
    if(e.type == SDL_MOUSEMOTION) {
        playerAngle += physics::createVec(e.motion.yrel / 200.0f, -e.motion.xrel / 200.0f, 0) * MOUSE_SENSITIVITY;
        if (playerAngle[0] < -PI_HALF) playerAngle[0] = -PI_HALF;
        if (playerAngle[0] > PI_HALF) playerAngle[0] = PI_HALF;
    }
}

#endif /* PlaygroundKeanu_hpp */
