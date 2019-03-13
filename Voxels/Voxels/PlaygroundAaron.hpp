//
//  PlaygroundAaron.hpp
//  Voxels
//
//  Created by Aaron Hodel on 13.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef PlaygroundAaron_hpp
#define PlaygroundAaron_hpp

#include "config/StaticConfig.hpp"
#include "graphics/Window.hpp"
#include "graphics/Shader.hpp"
#include "math/Physics.hpp"
#include "graphics/objects/Triangle.hpp"
#include "graphics/Chunk.hpp"

#include <vector>

#define TEST_FLOOR_SIZE 20

float *floorHeights = new float[TEST_FLOOR_SIZE * TEST_FLOOR_SIZE];
std::vector<graphics::objects::Triangle*> floorTriangles;
graphics::Shader *shader;
physics::vec3 playerPos = physics::createVec(0, -2, 0), playerAngle, moveVec;
float currentTime = 0;

static void initPlayground() {
    shader = graphics::loadFromFiles("./assets/shaders/shader.vert", "./assets/shaders/shader.frag");
    shader->bind();
    
#ifdef DEBUG_RANDOM
    math::Perlin perlin = math::Perlin(0x1234); // Contstant seed
#else
    math::Perlin perlin = math::Perlin((int) time(NULL));
#endif
    
    graphics::objects::Material m1 = graphics::objects::Material(physics::createVec(0, 0, 1, 1));
    graphics::objects::Material m2 = graphics::objects::Material(new graphics::Texture("assets/textures/cube/water.png"));
    for(int i = 0; i < TEST_FLOOR_SIZE * TEST_FLOOR_SIZE; i++) floorHeights[i] = 10.0f * perlin.noise((float) (i % TEST_FLOOR_SIZE) / 10.0f, 0, (float)(i / TEST_FLOOR_SIZE) / 10.0f);
    
    for(int i = 0; i < TEST_FLOOR_SIZE - 1; i++) {
        for(int j = 0; j < TEST_FLOOR_SIZE - 1; j++) {
            // Connect (i|j), (i+1|j), (i|j+1)
            // Connect (...
            
            physics::vec3 p1 = physics::createVec(i, floorHeights[i + j * TEST_FLOOR_SIZE], j);
            physics::vec3 p2 = physics::createVec(i + 1, floorHeights[i + 1 + j * TEST_FLOOR_SIZE], j);
            physics::vec3 p3 = physics::createVec(i, floorHeights[i + (j + 1) * TEST_FLOOR_SIZE], j + 1);
            floorTriangles.push_back(new graphics::objects::Triangle(shader, p1, p2, p3, m2));

            physics::vec3 p4 = physics::createVec(i + 1, floorHeights[i + 1 + (j + 1) * TEST_FLOOR_SIZE], j + 1);
            physics::vec3 p5 = physics::createVec(i, floorHeights[i + (j + 1) * TEST_FLOOR_SIZE], j + 1);
            physics::vec3 p6 = physics::createVec(i + 1, floorHeights[i + 1 + j * TEST_FLOOR_SIZE], j);
            floorTriangles.push_back(new graphics::objects::Triangle(shader, p4, p5, p6, m2));
        }
    }
}

void render(graphics::Window *window) {
    glClearColor(0, 0, 0, 1); // Clear background to black
    
    for (int i = 0; i < floorTriangles.size(); i++) floorTriangles[i]->render();
    
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
    
    /**
     if(window->isKeyPressed(SDL_SCANCODE_E)) playerAngle[2] -= 0.002;
     if(window->isKeyPressed(SDL_SCANCODE_Q)) playerAngle[2] += 0.002;
     */
    
    //limit the direction vector to length 1
    float len = moveVec.len();
    if (len > 1) moveVec /= len;
    
    playerPos += (physics::createVec(-0.1 * sin(playerAngle[1]), 0, 0.1 * cos(playerAngle[1])) * -moveVec[0]) * MOVESPEED;
    playerPos += (physics::createVec(0.1 * cos(playerAngle[1]), 0, 0.1 * sin(playerAngle[1])) * moveVec[2]) * MOVESPEED;
    playerPos += (physics::createVec(0.0, 0.1, 0.0) * moveVec[1]) * MOVESPEED;
}

void handleEvent(SDL_Event e) {
    if(e.type == SDL_MOUSEMOTION) {
        playerAngle += physics::createVec(e.motion.yrel / 200.0f, -e.motion.xrel / 200.0f, 0) * MOUSE_SENSITIVITY;
        if (playerAngle[0] < -PI_HALF) playerAngle[0] = -PI_HALF;
        if (playerAngle[0] > PI_HALF) playerAngle[0] = PI_HALF;
    }
}



#endif /* PlaygroundAaron_hpp */
