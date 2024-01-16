#version 330

in vec2 fragment_uv;

out vec3 color;

uniform sampler2D texture_sampler;

void main() {
    color = texture(texture_sampler, fragment_uv).rgb;
}
