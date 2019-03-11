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

graphics::objects::Object *voxel;
graphics::Shader *shader;

void render() {
	glClearColor(1, 1, 1, 1); // Render stuff
    voxel->render();
}

void handleEvent(SDL_Event e) {

}

int main(int argc, char **args) {
    graphics::Window window = graphics::Window();
    
    voxel = new graphics::objects::Voxel();
	shader = graphics::loadFromFiles("./assets/shaders/shader.vert", "./assets/shaders/shader.frag");
    shader->bind();
    
	window.addEventFunc(handleEvent);
	window.addRenderFunc(render);
    window.run();
    return 0;
}
