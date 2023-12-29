#version 330

in vec3 position;
in vec2 uv;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec2 fragment_uv;

void main() {
    fragment_uv = uv;
    gl_Position = projection * view * model * vec4(position, 1);
}
