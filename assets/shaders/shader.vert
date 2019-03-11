#version 330 core

#include "assets/shaders/util/transformations.glsl"

layout (location = 0) in vec3 vertPosition;
layout (location = 1) in vec2 uvPosition;

uniform sampler2D tex;
uniform float time;

out vec4 pos;
out vec4 col;
out vec2 uv;

void main() {
    vec3 trans = vec3(0, 0, -1);
	gl_Position = perspective(PI / 2.0, 0.1, 100) * translate(-trans) * rotate_y(time) * translate(trans) * vec4(vertPosition, 1);

	col = vec4(1, 0, 1, 1);
	pos = gl_Position;
    uv = uvPosition;
}
