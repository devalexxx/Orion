#version 330

in vec3 position;
in vec3 normal;
in vec2 uv;

void main() {
    fragment_uv = uv;
    gl_Position = projection * view * model * vec4(position.xy, 0, 1);
}
