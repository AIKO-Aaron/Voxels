//
//  main.cpp
//  Voxels
//
//  Created by Aaron Hodel on 07.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "config/StaticConfig.h"
#include "graphics/Window.hpp"

int main(int argc, const char **argv) {
    graphics::Window window = graphics::Window();
    window.run();
    return 0;
}
