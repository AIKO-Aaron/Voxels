#version 330 core

layout (location = 0) in vec3 vertPosition;

out vec4 pos;
out vec4 col;

void main() {
	gl_Position = vec4(vertPosition, 1);

	col = vec4(1, 0, 1, 1);
	pos = gl_Position;
}