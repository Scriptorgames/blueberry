#version 420 core

in vec2 vUV;

layout(location = 0) out vec4 Color;

void main() {
    Color = vec4(vUV, 0.0, 1.0);
}
