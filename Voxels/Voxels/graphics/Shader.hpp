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
#include "../config/StaticConfig.hpp"
#include "../math/Physics.hpp"

namespace graphics {
    class Shader {
    private:
        GLuint shaderID;
        
    public:
        Shader(const char *vertSrc, const char *fragSrc);
        
        inline void bind() { glUseProgram(shaderID); }
        
        inline void uniformf(const char *name, physics::vec2 v) { glUniform2f(glGetUniformLocation(shaderID, name), v[0], v[1]); };
        inline void uniformf(const char *name, physics::vec3 v) { glUniform3f(glGetUniformLocation(shaderID, name), v[0], v[1], v[2]); };
        inline void uniformf(const char *name, physics::vec4 v) { glUniform4f(glGetUniformLocation(shaderID, name), v[0], v[1], v[2], v[3]); };

        inline void uniformf(const char *name, physics::mat2 v) { glUniformMatrix2fv(glGetUniformLocation(shaderID, name), 1, false, v.values); };
        inline void uniformf(const char *name, physics::mat3 v) { glUniformMatrix3fv(glGetUniformLocation(shaderID, name), 1, false, v.values); };
        inline void uniformf(const char *name, physics::mat4 v) { glUniformMatrix4fv(glGetUniformLocation(shaderID, name), 1, false, v.values); };
    };
    
    extern Shader *loadFromFiles(const char *vertPath, const char *fragPath);
}

#endif /* Shader_hpp */
