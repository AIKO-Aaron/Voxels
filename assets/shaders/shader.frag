#version 330 core

uniform sampler2D tex;

in vec4 pos;
in vec2 uv;
in vec4 col;

out vec4 fragColor;

void main() {
    fragColor = texture(tex, uv); //col;
}
