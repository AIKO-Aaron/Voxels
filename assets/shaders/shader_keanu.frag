#version 330 core

#define NUM_LIGHTS 1
#include "assets/shaders/util/lights_k.glsl"

uniform lightSource lights[NUM_LIGHTS];
uniform int numLights;

uniform material mat;
uniform vec4 color;

in vec3 transCameraPos;
in vec4 transObjectPos;
in vec2 uv;
in vec4 objectNormalvector;
in mat4 view;

out vec4 fragColor;

void main() {
    //fragColor = mat.isTextured == 1 ? texture(mat.tex, uv) : mat.color;
    vec3 col = vec3(0, 0, 0);
    for(int i = 0; i < numLights; i++) {
        col += calcLight(mat, lights[i], transCameraPos, transObjectPos.xyz, objectNormalvector.xyz, uv, view);
    }
    fragColor = vec4(col, 1.0f);
}
