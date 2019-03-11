//
//  Chunk.hpp
//  Voxels
//
//  Created by Keanu Gleixner on 11.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Chunk_hpp
#define Chunk_hpp

#include <stdio.h>
#include <vector>

#include "objects/Voxel.hpp"

namespace graphics{    
    class Chunk{
        
    public:
        int xCord,yCord;
        
        std::vector<objects::Voxel*> voxels;
        
        Chunk(int x, int y);
        ~Chunk();
        
        void render();
    };
}

#endif /* Chunk_hpp */
