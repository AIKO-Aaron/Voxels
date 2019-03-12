//
//  Physics.hpp
//  Voxels
//
//  Created by Aaron Hodel on 10.03.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Physics_hpp
#define Physics_hpp

#include "Math.hpp"

namespace physics {
    
    typedef math::Vector<2> vec2; // you can now write vec2 for a 2D vector
    typedef math::Vector<3> vec3; // and vec3 for a 3D one
    typedef math::Vector<4> vec4; // and vec4 for a 4D one
    
    typedef math::Matrix<2, 2> mat2; // Like GLSL
    typedef math::Matrix<3, 3> mat3; // Like GLSL
    typedef math::Matrix<4, 4> mat4; // Like GLSL
    
    static vec2 createVec(float x, float y) { vec2 v = vec2(); v[0] = x; v[1] = y; return v; }
    static vec3 createVec(float x, float y, float z) { vec3 v = vec3(); v[0] = x; v[1] = y; v[2] = z; return v; }
    static vec4 createVec(float x, float y, float z, float w) { vec4 v = vec4(); v[0] = x; v[1] = y; v[2] = z; v[3] = w; return v; }

}

#endif /* Physics_hpp */
