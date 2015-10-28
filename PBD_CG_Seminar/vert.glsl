#version 400
//Lighting struct
struct LightSource
{
    vec3 pos;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform mat4 modelview;
uniform mat4 projection; 

//Lighting Block
layout(std140) uniform LightSourceBlock{
    LightSource Light[12];
};

//Vertex input attribs
in vec3 vertex;
in vec3 normal;
in vec2 uv;
in vec3 ambient;
in vec3 diffuse;
in vec3 specular;
in float shininess;
in float mass;
in float velocity;

//Fragment input params
out vec4 frag_color;

void main(void) {
    frag_color = vec4(1.0,0.0,0.0,1.0);
    gl_Position = projection * modelview * vec4(vertex,1.0);
}
