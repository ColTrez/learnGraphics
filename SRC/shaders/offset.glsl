#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform vec3 offset;

out vec3 ourColor;

void main(){
    vec3 sum = aPos + offset;
    gl_Position = vec4(sum, 1.0);
    ourColor = aColor;
}
