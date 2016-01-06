#version 130
//Lighting struct
struct LightSource
{
    vec3 pos;
    vec3 amb;
    vec3 dif;
    vec3 spec;
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 modelView;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform vec3 cameraPos;

//Lighting Block
uniform LightSource light[12];
uniform vec3 a;

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
out vec3 frag_position;
out vec3 frag_normal;

void main(void) {

    frag_normal = normal;
    frag_position = vertex;
    gl_Position = projection * modelView * vec4(vertex,1.0);
}
