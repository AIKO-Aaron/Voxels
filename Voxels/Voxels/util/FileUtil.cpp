//
//  FileUtil.cpp
//  Voxels
//
//  Created by Aaron Hodel on 08.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "FileUtil.hpp"

util::filedata util::readFile(const char *path) {
#ifdef __APPLE__
    FILE *f = fopen(path, "rb");
#else
    
#endif
    
    if(!f) {
        printf("[ERROR] File %s could not be opened\n", path);
        return { nullptr, 0 };
    }
    
    filedata fd;
    fseek(f, 0, SEEK_END);
    fd.size = ftell(f);
    fd.data = (uint8_t*) malloc(fd.size);
    fseek(f, 0, SEEK_SET);
    fread(fd.data, 1, fd.size, f);
    fclose(f);
    
    return fd;
}
