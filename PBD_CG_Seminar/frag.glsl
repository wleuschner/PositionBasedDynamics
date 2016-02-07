#version 130
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

uniform LightSource light[12];
uniform Material material;

uniform mat4 view;
uniform mat4 model;
uniform mat4 modelView;
uniform mat3 normalMatrix;

uniform vec3 position;
uniform bool doubleFaced;

in vec3 frag_position;
in vec3 frag_normal;

out vec4 fragColor;

void main(void) {
    vec3 normal = normalize(frag_normal);
    vec3 pos = frag_position;
    vec3 ldir = normalize(vec3((view*vec4(light[0].pos,1.0)).xyz) - pos);

    if(doubleFaced)
    {
        if(dot(ldir,normal)<0)
        {
            normal = -normal;
        }
    }

    vec3 reflected = reflect(-ldir,frag_normal);
    vec3 vdir = normalize(-pos);

    float dif = max(dot(ldir,normal),0.0);
    float spec = 0.0;
    if(dif>0.0)
    {
        float specAngle = max(dot(reflected,vdir),0.0);
        spec = pow(specAngle,material.shininess);
    }
    vec3 color = light[0].amb*material.amb+light[0].dif*material.dif*dif+light[0].spec*material.spec*spec;
    fragColor = vec4(color,1.0);
}
