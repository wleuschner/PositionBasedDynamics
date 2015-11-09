#version 400

in vec4 frag_pos;
in vec4 frag_color;

out vec4 fragColor;

void main(void) {
    fragColor = frag_color;
}
