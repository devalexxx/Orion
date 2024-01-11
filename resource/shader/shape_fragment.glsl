#version 330

uniform sampler2D texture_sampler;
uniform vec4 uniform_color;

uniform int sample_mode;

in vec4 fragment_color;
in vec2 fragment_uv;

out vec4 color;

void main() {
    if (sample_mode == 0) {
        color = texture(texture_sampler, fragment_uv);
    }
    else if (sample_mode == 1) {
        color = fragment_color;
    }
    else {
        color = uniform_color;
    }
}
