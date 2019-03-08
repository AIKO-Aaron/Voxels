//
//  FileUtil.hpp
//  Voxels
//
//  Created by Aaron Hodel on 08.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef FileUtil_hpp
#define FileUtil_hpp

#include <stdint.h>
#include <fstream>
#include <stdlib.h>
#include <string>

namespace util {
 
    typedef struct {
        uint8_t *data;
        uint64_t size;
    } filedata;
    
    extern filedata readFile(const char *path);
    
}

#endif /* FileUtil_hpp */
