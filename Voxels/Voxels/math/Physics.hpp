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
    
    static mat2 createMat(vec2 x, vec2 y) {
        mat2 v = mat2();
        v(0, 0) = x[0];
        v(1, 0) = x[1];
        v(0, 1) = y[0];
        v(1, 1) = y[1];
        return v;
    }
    
    static mat3 createMat(vec3 x, vec3 y, vec3 z) {
        mat3 v = mat3();
        v(0, 0) = x[0];
        v(1, 0) = x[1];
        v(2, 0) = x[2];
        v(0, 1) = y[0];
        v(1, 1) = y[1];
        v(2, 1) = y[2];
        v(0, 2) = z[0];
        v(1, 2) = z[1];
        v(2, 2) = z[2];
        return v;
    }
    
    static mat2 createMat(float a1, float a2, float a3, float a4) {
        mat2 v = mat2();
        v(0, 0) = a1;
        v(1, 0) = a2;
        v(0, 1) = a3;
        v(1, 1) = a4;
        return v;
    }
    
    static mat3 createMat(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9) {
        mat3 v = mat3();
        v(0, 0) = a1;
        v(1, 0) = a2;
        v(2, 0) = a3;
        v(0, 1) = a4;
        v(1, 1) = a5;
        v(2, 1) = a6;
        v(0, 2) = a7;
        v(1, 2) = a8;
        v(2, 2) = a9;
        return v;
    }
}

#endif /* Physics_hpp */
