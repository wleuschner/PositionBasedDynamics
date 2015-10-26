#version 400

uniform mat4 modelview;
uniform mat4 projection;
in vec4 vertex;

void main(void) {
    gl_Position = projection * modelview * vertex;
}
