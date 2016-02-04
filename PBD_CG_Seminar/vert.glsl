#version 130
//Lighting struct
struct LightSource
{
    vec3 pos;
    vec3 amb;
    vec3 dif;
    vec3 spec;
};

struct Material
{
    vec3 amb;
    vec3 dif;
    vec3 spec;
    float shininess;
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 modelView;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform vec3 cameraPos;

//Lighting Block
uniform LightSource light[12];
uniform Material material;

uniform vec3 position;

//Vertex input attribs
in vec3 vertex;
in vec3 normal;
in vec2 uv;
in float mass;
in float velocity;

//Fragment input params
out vec3 frag_position;
out vec3 frag_normal;

void main(void) {

    frag_normal = normalMatrix * normal;
    frag_position = (modelView * vec4(vertex,1.0)).xyz;
    gl_Position = projection * modelView * vec4(vertex,1.0);
}
