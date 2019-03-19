#version 330 core

#include "assets/shaders/util/transformations.glsl"

layout (location = 0) in vec3 vertPosition;
layout (location = 1) in vec2 uvPosition;

uniform float time;
uniform vec3 cameraPos;
uniform vec3 playerView;

uniform vec3 vertPos; // The current vertex translation
uniform vec3 vertRot; // The current vertex rotation

out vec4 pos;
out vec2 uv;

void main() {
	// gl_Position = perspective(PI / 2.0, 0.1, 100) * rotate_camera(playerView) * translate(cameraPos) * translate(-vertPos) * rotate(-vertRot) * vec4(vertPosition, 1);
	gl_Position = perspective(PI / 2.0, 0.1, 100) * rotate_camera(playerView) * translate(cameraPos) * translate(-vertPos) * rotate(-vertRot) * vec4(vertPosition, 1);

	pos = gl_Position;
    uv = uvPosition;
}
