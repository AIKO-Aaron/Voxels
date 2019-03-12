#version 330 core

#include "assets/shaders/util/transformations.glsl"

layout (location = 0) in vec3 vertPosition;
layout (location = 1) in vec2 uvPosition;

uniform float time;
uniform vec3 playerPos;
uniform vec3 playerView;

out vec4 pos;
out vec2 uv;

void main() {
	gl_Position = perspective(PI / 2.0, 0.1, 100) * (rotate_x(playerView.x) * rotate_y(playerView.y) * rotate_z(playerView.z)) * translate(playerPos) * vec4(vertPosition, 1);

	pos = gl_Position;
    uv = uvPosition;
}
