#version 330 core

uniform sampler2D tex;
uniform int isTextured;
uniform vec4 color;

in vec4 pos;
in vec2 uv;

out vec4 fragColor;

void main() {
    fragColor = isTextured == 1 ? texture(tex, uv) : color;
}
