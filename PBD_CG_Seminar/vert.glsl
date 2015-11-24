#version 140
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
uniform mat4 projection;
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
out vec4 frag_color;

void main(void) {
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 n = normalize(normalMatrix * normal);
    vec3 p = (model * vec4(vertex,1.0)).xyz;

    vec3 l_dir = normalize(light[0].pos - p);
    float dif = max(dot(l_dir,n),0.0);
    float spec = 0.0;
    if(dif>0.0)
    {
        spec = pow(dot(reflect(l_dir,n),vec3(0.0,0.0,-1.0)),shininess);
    }
    float r=light[0].amb.r+light[0].dif.r*dif+light[0].spec.r*specular.r*spec;
    float g=light[0].amb.g+light[0].dif.g*dif+light[0].spec.g*specular.g*spec;
    float b=light[0].amb.b+light[0].dif.b*dif+light[0].spec.b*specular.b*spec;
    frag_color = vec4(r,g,b,1.0);
    gl_Position = projection * view * model * vec4(vertex,1.0);
}
