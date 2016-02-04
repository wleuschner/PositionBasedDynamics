#version 130
uniform mat4 depthMVP;
in vec3 vertex;

void main(void)
{
    gl_Position = depthMVP * vertex
}
