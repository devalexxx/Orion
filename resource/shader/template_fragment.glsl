#version 330

uniform sampler2D texture_sampler;

in vec2 fragment_uv;

out vec4 color;

void main() {
    color = texture(texture_sampler, fragment_uv);
}
