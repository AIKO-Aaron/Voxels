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
	gl_Position = translate(vec3(0.5, 0.5, -0.5)) * rotate_y(time) * translate(vec3(-0.5, -0.5, 0.5)) * vec4(vertPosition, 1);

	col = vec4(1, 0, 1, 1);
	pos = gl_Position;
    uv = uvPosition;
}
