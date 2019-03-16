//
//  Vector.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 29.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <cmath>
#include <stdio.h>

namespace math {
    
    // Just tell vector there exists a matrix class out there somewhere
    template<int M, int N>
    class Matrix;
    
    template<int D>
    class Vector {
    private:
        float *values = new float[D];
        
    public:
        Vector();
        Vector(float v);
        Vector(float *v);
        
        inline float &operator[](int index) { return values[index]; }
        
        float dot(Vector<D> other);
        inline float operator *(Vector<D> other) { return dot(other); }
        
        inline Vector<D> operator +(Vector<D> other) { Vector<D> result; for(int i = 0; i < D; i++) result[i] = values[i] + other[i]; return result; }
        inline Vector<D> operator -(Vector<D> other) { Vector<D> result; for(int i = 0; i < D; i++) result[i] = values[i] - other[i]; return result; }
        inline Vector<D> operator +=(Vector<D> other) { for(int i = 0; i < D; i++) values[i] += other[i]; return *this; }
        inline Vector<D> operator -=(Vector<D> other) { for(int i = 0; i < D; i++) values[i] -= other[i]; return *this; }

        inline Vector<D> operator *(float scalar) { Vector<D> result; for(int i = 0; i < D; i++) result[i] = values[i] * scalar; return result; }
        inline Vector<D> operator /(float scalar) { Vector<D> result; for(int i = 0; i < D; i++) result[i] = values[i] / scalar; return result; }
        inline Vector<D> operator *=(float scalar) { for(int i = 0; i < D; i++) values[i] *= scalar; return *this; }
        inline Vector<D> operator /=(float scalar) { for(int i = 0; i < D; i++) values[i] /= scalar; return *this; }

		// Elementwise operators
		inline Vector<D> mult(Vector<D> other) { Vector<D> result; for (int i = 0; i < D; i++) result[i] = values[i] * other[i]; return result; }
		inline Vector<D> div(Vector<D> other) { Vector<D> result; for (int i = 0; i < D; i++) result[i] = values[i] / other[i]; return result; }

        inline Vector<D> operator +(float vec) { Vector<D> result; for(int i = 0; i < D; i++) result[i] = values[i] + vec; return result; }
        inline Vector<D> operator -(float vec) { Vector<D> result; for(int i = 0; i < D; i++) result[i] = values[i] - vec; return result; }
        inline Vector<D> operator +=(float vec) { for(int i = 0; i < D; i++) values[i] += vec; return *this; }
        inline Vector<D> operator -=(float vec) { for(int i = 0; i < D; i++) values[i] -= vec; return *this; }
            
		inline Vector<D> copy() { return Vector<D>(values); } // Copy the vector and return it

        inline void normalize() { float len = 0; for(int i = 0; i < D; i++) len += values[i] * values[i]; operator/=(1.0f / sqrt(len)); }
        inline float len() { float len = 0; for(int i = 0; i < D; i++) len += values[i] * values[i]; return sqrt(len); }
        inline float lensq() { float len = 0; for(int i = 0; i < D; i++) len += values[i] * values[i]; return len; }
    };
}

template <int D>
math::Vector<D>::Vector() {
    for(int i = 0; i < D; i++) values[i] = 0;
}

template <int D>
math::Vector<D>::Vector(float v) {
    for(int i = 0; i < D; i++) values[i] = v;
}

template <int D>
math::Vector<D>::Vector(float *v) {
    for(int i = 0; i < D; i++) values[i] = v[i];
}

template <int D>
float math::Vector<D>::dot(Vector<D> other) {
    float result = 0.0;
    for(int i = 0; i < D; i++) result += other[i] * values[i];
    return result;
}

namespace math {
 
    static math::Vector<3> cross(Vector<3> a, Vector<3> b) {
        return math::Vector<3>(new float[3]{ a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0] });
    }
    
}

#endif /* Vector_hpp */
