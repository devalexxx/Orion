#version 330

in vec3 position;
in vec3 normal;
in vec2 uv;

in vec4 color;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec2 fragment_uv;
out vec4 fragment_color;

void main() {
    vec3 n = normal;
    fragment_uv = uv;
    fragment_color = color;
    gl_Position = projection * view * model * vec4(position, 1);
}
