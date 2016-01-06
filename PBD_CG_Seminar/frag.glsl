#version 130
struct LightSource
{
    vec3 pos;
    vec3 amb;
    vec3 dif;
    vec3 spec;
};

uniform LightSource light[12];
uniform mat4 view;
uniform mat4 model;
uniform mat4 modelView;
uniform mat3 normalMatrix;

in vec3 frag_position;
in vec3 frag_normal;

out vec4 fragColor;

void main(void) {
    vec3 normal = normalize(normalMatrix*frag_normal);
    vec3 pos = vec3(modelView * vec4(frag_position,1.0));

    vec3 ldir = normalize(vec3(view * vec4(light[0].pos,1.0)) - pos);
    vec3 reflected = normalize(reflect(ldir,frag_normal));

    float dif = max(dot(ldir,normal),0.0);
    float spec = 0.0;
    if(dif>0.0)
    {
        spec = pow(max(dot(reflected,vec3(0.0,0.0,-1.0)),0.0),32.0);
    }
    float r=light[0].amb.r+light[0].dif.r*0.6*dif+light[0].spec.r*0.8*spec;
    float g=light[0].amb.g+light[0].dif.g*0.6*dif+light[0].spec.g*0.8*spec;
    float b=light[0].amb.b+light[0].dif.b*0.6*dif+light[0].spec.b*0.8*spec;
    fragColor = vec4(r,g,b,1.0);
}
