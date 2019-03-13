//
//  main.cpp
//  Voxels
//
//  Created by Aaron Hodel on 07.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifdef _PROJ_TEST_AARON
#  include "PlaygroundAaron.hpp"
#else
#  include "PlaygroundKeanu.hpp"
#endif

int main(int argc, char **args) {
    graphics::Window window = graphics::Window();
   
    initPlayground();
	window.addEventFunc(handleEvent);
	window.addRenderFunc(render);
    
    window.run();
    return 0;
}
