//
//  Shader.hpp
//  Voxels
//
//  Created by Aaron Hodel on 08.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <GL/glew.h>
#include <stdlib.h>
#include <string>
#include "../util/FileUtil.hpp"

namespace graphics {
    class Shader {
    private:
        GLuint shaderID;
        
    public:
        Shader(const char *vertSrc, const char *fragSrc);
        
        inline void bind() { glUseProgram(shaderID); }
    };
    
    extern Shader *loadFromFiles(const char *vertPath, const char *fragPath);
}

#endif /* Shader_hpp */
