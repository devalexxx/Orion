#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

uniform mat4 mvp;

out vec2 fragment_uv;

void main() {
    gl_Position = mvp * vec4(position, 1);
    fragment_uv = uv;
}
