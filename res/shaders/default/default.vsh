#version 420 core

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 UV;

out vec2 vUV;

void main() {
    gl_Position = Position;
    vUV = UV;
}
