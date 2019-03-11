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

graphics::objects::Object *voxel;
std::vector<graphics::Chunk*> chunks;

graphics::Shader *shader;
float currentTime = 0;

void render() {
	glClearColor(1, 1, 1, 1); // Render stuff

    for (int i = 0; i < chunks.size(); i++) {
        chunks[i]->render();
    }
    
    shader->uniformf("time", currentTime);
    
    currentTime += 0.01;
}

void handleEvent(SDL_Event e) {

}

int main(int argc, char **args) {
    //push a test voxel into a junk
    chunks.push_back(new graphics::Chunk(0,0));
    chunks[0]->voxels.push_back(new graphics::objects::Voxel());
    
    graphics::Window window = graphics::Window();
    
    voxel = new graphics::objects::Voxel();
	shader = graphics::loadFromFiles("./assets/shaders/shader.vert", "./assets/shaders/shader.frag");
    shader->bind();
    
	window.addEventFunc(handleEvent);
	window.addRenderFunc(render);
    window.run();
    return 0;
}
