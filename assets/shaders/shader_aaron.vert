#version 330 core

#include "assets/shaders/util/transformations.glsl"

layout (location = 0) in vec3 vertPosition;
layout (location = 1) in vec2 uvPosition;
layout (location = 2) in vec3 vertNormal;

uniform float time;
uniform vec3 cameraPos;
uniform vec3 cameraOffset = vec3(0, 0, 0); // The current camera offset
uniform vec3 playerView;

uniform vec3 vertPos = vec3(0, 0, 0); // The current vertex translation
uniform vec3 anchorPos = vec3(0, 0, 0); // The point around which to rotate the vertex
uniform vec3 vertRot = vec3(0, 0, 0); // The current vertex rotation

out vec3 viewPos;
out vec4 pos;
out vec2 uv;
out vec4 normal;
out mat4 view;

mat4 createTransformationMatrix() {
    return perspective(PI / 2.0f, 0.1, 100) // We have a 3D perspective (Things further back are smaller)
            * translate(-cameraOffset) // Move the camera according to the offset specified
            * rotate_camera(playerView) // Rotate the camera, so the player sees the right things
            * translate(cameraPos) // Move the world so the camera is moved to its position
            * translate(-vertPos) // Move vertex to its position --> Move it to 0,0,0
            * translate(anchorPos) // Translate back
            * rotate(-vertRot) // Rotate around 0,0,0
            * translate(-anchorPos); // Translate anchorPos to 0,0,0
}

void main() {
    view = createTransformationMatrix();
    gl_Position = view * vec4(vertPosition, 1);
    
    // Give stuff to Fragment shader
    normal = normalize(vec4(vertNormal, 0)); // Direction (w = 0) --> Translations don't get applied
	pos = gl_Position;
    uv = uvPosition;
    viewPos = normalize(view * vec4(cameraPos, 0)).xyz;
}
