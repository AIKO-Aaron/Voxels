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
#include "graphics/objects/Mesh.hpp"
#include "graphics/Chunk.hpp"

#include <vector>

#define TEST_FLOOR_SIZE 5

physics::Env env;
float *floorHeights = new float[TEST_FLOOR_SIZE * TEST_FLOOR_SIZE];
std::vector<graphics::objects::Triangle*> floorTriangles;
graphics::objects::Mesh *floorMesh;
std::vector<graphics::objects::Voxel*> physObj;
graphics::objects::Voxel *player;
graphics::Shader *shader;
physics::vec3 playerPos = physics::createVec(0, 0, 0), playerAngle;
float currentTime = 0;

physics::vec3 gravity(physics::Element *element) {
	if (element->position[1] > 0) {
		element->position[1] = 0;
		element->velocity[1] = 0;
	}
	return physics::createVec(0, 0.001f * element->mass, 0);
}

static void initPlayground() {
    shader = graphics::loadFromFiles("./assets/shaders/shader_aaron.vert", "./assets/shaders/shader_aaron.frag");
    shader->bind();
    
    // 2 --> 6
    // 3 --> 6 * 4
    // n --> 6 * (n - 1) * (n - 1)
    
    shader->uniformi("numLights", 1);
    
    // Directional light
    shader->uniformf("lights[0].position", physics::createVec(1.0f, 1.0f, 0.0, 0.0f));
    shader->uniformf("lights[0].attenuation", physics::createVec(1.0, 0.14f, 0.07f));
    shader->uniformf("lights[0].ambientColor", physics::createVec(0.5f, 0.5f, 0.5f));
    shader->uniformf("lights[0].diffuseColor", physics::createVec(1.0f, 1.0f, 1.0f));
    shader->uniformf("lights[0].specularColor", physics::createVec(0.0f, 0.0f, 0.0f));
    shader->uniformf("lights[0].brightness", 0.2f);
    
    
    // Point light
    /*shader->uniformf("lights[1].position", physics::createVec(1, 10, 1, 1));
    shader->uniformf("lights[1].attenuation", physics::createVec(1.0, 0.14f, 0.07f));
    shader->uniformf("lights[1].ambientColor", physics::createVec(0.0f, 0.0f, 0.1f));
    shader->uniformf("lights[1].diffuseColor", physics::createVec(0.0f, 0.0f, 0.6f));
    shader->uniformf("lights[1].specularColor", physics::createVec(0.0f, 0.0f, 1.0f));
    shader->uniformf("lights[1].brightness", 1.0f);*/
    
#ifdef DEBUG_RANDOM
    math::Perlin perlin = math::Perlin(0x1234); // Contstant seed
#else
    math::Perlin perlin = math::Perlin((int) time(NULL));
#endif

	env.addForceFunc(gravity);
    
	graphics::objects::Material mp = graphics::objects::Material(physics::createVec(1, 1, 1, 1));

	graphics::objects::Material m1 = graphics::objects::Material(physics::createVec(0, 0, 1, 1));
    graphics::objects::Material m2 = graphics::objects::Material(new graphics::Texture("assets/textures/cube/water.png"));
    for(int i = 0; i < TEST_FLOOR_SIZE * TEST_FLOOR_SIZE; i++) floorHeights[i] = 5.0f * (float) perlin.noise((float) (i % TEST_FLOOR_SIZE) / 10.0f, 0, (float)(i / TEST_FLOOR_SIZE) / 10.0f);
    
	player = new graphics::objects::Voxel(shader, BLANK, 0, -1, 0, 1, 1, 1, mp); // Centered around 0,0,0

	physObj.push_back(new graphics::objects::Voxel(shader, BLANK, 0, -1, -1, 1, 1, 1, m1));
	physObj.push_back(new graphics::objects::Voxel(shader, BLANK, 0, -3, -1, 1, 1, 1, graphics::objects::Material(physics::createVec(1, 1, 1, 1))));
    physObj.push_back(new graphics::objects::Voxel(shader, BLANK, 0, -6, -1, 1, 1, 1, graphics::objects::Material(physics::createVec(1, 0, 0, 1))));
    //physObj.push_back(new graphics::objects::Voxel(shader, BLANK, 0, -10, -1, 1, 1, 1, graphics::objects::Material(physics::createVec(1, 0, 1, 1))));
	//physObj.push_back(new graphics::objects::Voxel(shader, BLANK, 0, -20, -1, 1, 1, 1, graphics::objects::Material(physics::createVec(1, 0, 1, 1))));
    // physObj[2]->mass *= 40;
    for (graphics::objects::Voxel *v : physObj) env.addElement(v);


	std::vector<physics::vec3> points;
    m2.shininess = 32.0f;
    for(int i = 0; i < TEST_FLOOR_SIZE - 1; i++) {
        for(int j = 0; j < TEST_FLOOR_SIZE - 1; j++) {
            physics::vec3 p1 = physics::createVec((float)i, floorHeights[i + j * TEST_FLOOR_SIZE], (float)j);
            physics::vec3 p2 = physics::createVec((float)i + 1.0f, floorHeights[i + 1 + j * TEST_FLOOR_SIZE], (float)j);
            physics::vec3 p3 = physics::createVec((float)i, floorHeights[i + (j + 1) * TEST_FLOOR_SIZE], (float)j + 1);
            //floorTriangles.push_back(new graphics::objects::Triangle(shader, p1, p2, p3, m2));
			points.push_back(p1);
			points.push_back(p2);
			points.push_back(p3);

            physics::vec3 p4 = physics::createVec((float)i + 1.0f, floorHeights[i + 1 + (j + 1) * TEST_FLOOR_SIZE], (float)j + 1.0f);
            physics::vec3 p5 = physics::createVec((float)i, floorHeights[i + (j + 1) * TEST_FLOOR_SIZE], (float)j + 1.0f);
            physics::vec3 p6 = physics::createVec((float)i + 1.0f, floorHeights[i + 1 + j * TEST_FLOOR_SIZE], (float)j);
            //floorTriangles.push_back(new graphics::objects::Triangle(shader, p4, p5, p6, m2));
			points.push_back(p4);
			points.push_back(p5);
			points.push_back(p6);
		}
    }

	floorMesh = new graphics::objects::Mesh(shader, points, m2);
	env.addElement(floorMesh);
}

void render(graphics::Window *window) {
    glClearColor(0, 0, 0, 1); // Clear background to black
    
	env.applyForces();

    for (size_t i = 0; i < floorTriangles.size(); i++) floorTriangles[i]->render();
	player->render();
	for (graphics::objects::Voxel *v : physObj) v->render();
	floorMesh->render();

	physics::vec3 viewVec = physics::createVec(
		sin(playerAngle[1]) * (cos(playerAngle[0])),
		sin(playerAngle[0]), 
		cos(playerAngle[1]) * (cos(playerAngle[0])));

	physics::vec3 viewdir = physics::createVec(0, 0, -2); // Which way wer're facing (in world space)

    shader->uniformf("time", currentTime);
    shader->uniformf("cameraPos", player->position);
	shader->uniformf("cameraOffset", viewdir * 1);
	shader->uniformf("playerView", playerAngle);
    
    currentTime += 0.01f;
    
	physics::vec3 moveVec;
    if(window->isKeyPressed(SDL_SCANCODE_D)) moveVec -= physics::createVec(0, 0, MOVESPEED);
    if(window->isKeyPressed(SDL_SCANCODE_A)) moveVec += physics::createVec(0, 0, MOVESPEED);
    if(window->isKeyPressed(SDL_SCANCODE_W)) moveVec += physics::createVec(MOVESPEED, 0, 0);
    if(window->isKeyPressed(SDL_SCANCODE_S)) moveVec -= physics::createVec(MOVESPEED, 0, 0);
    if(window->isKeyPressed(SDL_SCANCODE_SPACE)) moveVec -= physics::createVec(0, MOVESPEED, 0);
    if(window->isKeyPressed(SDL_SCANCODE_LSHIFT)) moveVec += physics::createVec(0, MOVESPEED, 0);
	moveVec *= 0.1f;

	moveVec = physics::createMat(
		sin(playerAngle[1]), 0, -cos(playerAngle[1]),
		0, 1, 0,
		cos(playerAngle[1]), 0, sin(playerAngle[1])) * moveVec;

	player->move(moveVec);
	playerPos += moveVec;
}

void handleEvent(SDL_Event e) {
    if(e.type == SDL_MOUSEMOTION) {
        playerAngle += physics::createVec(e.motion.yrel / 200.0f, -e.motion.xrel / 200.0f, 0) * MOUSE_SENSITIVITY;
        if (playerAngle[0] < -PI_HALF) playerAngle[0] = -PI_HALF;
        if (playerAngle[0] > PI_HALF) playerAngle[0] = PI_HALF;

		player->rotate(physics::createVec(e.motion.yrel / 200.0f, -e.motion.xrel / 200.0f, 0) * MOUSE_SENSITIVITY);
		if (player->getData().rotation[0] < -PI_HALF) player->getData().rotation[0] = -PI_HALF;
		if (player->getData().rotation[0] > PI_HALF) player->getData().rotation[0] = PI_HALF;
    }
}



#endif /* PlaygroundAaron_hpp */
