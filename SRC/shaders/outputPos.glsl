#version 330 core

layout (location = 0) in vec3 aPos;

out Data {
   out vec3 outPos;
};

void main(){
    gl_Position = vec4(aPos, 1.0);
    outPos = aPos;
}
