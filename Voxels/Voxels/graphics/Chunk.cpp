//
//  Chunk.cpp
//  Voxels
//
//  Created by Keanu Gleixner on 11.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Chunk.hpp"

using namespace graphics;

Chunk::Chunk(int x, int y) : xCord(x), yCord(y){
    
}

void Chunk::render(){
    for (int i = 0; i < voxels.size(); i++) {
        voxels[i]->render();
    }
}
