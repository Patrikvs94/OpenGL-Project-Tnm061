#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;
layout(location = 3) in vec3 Tangent;

uniform mat4 MV;
uniform mat4 P;
uniform float time;
uniform vec3 l_pos[10];

out vec2 stCoords;
out vec3 lightDirection[10];
out vec4 eyeSpacePos;
out mat3 TBN;
out float lightDistance[10];
out float t;

void main(){
    
     vec3 pos = mat3(MV) * Position;
  gl_Position = (P * MV) * vec4(Position, 1.0f);
    vec3 T = normalize(vec3(MV * vec4(Tangent,   0.0)));
    vec3 N = normalize(vec3(MV * vec4(Normal,    0.0)));
    
    T = normalize(T - dot(T, N) * N);
    
    vec3 B= cross(T,N);
    
    TBN = mat3(T, B, N);
    t=time;
    stCoords = TexCoord;
    
    for(int i=0;i<10;++i)
    {
        lightDirection[i] = (pos-l_pos[i]);
        lightDistance[i]=length(lightDirection[i]);
        lightDirection[i]=normalize(lightDirection[i]);
    }

  //Variable used for calculating fog :)
  eyeSpacePos = MV * vec4(Position, 1.0);
}
