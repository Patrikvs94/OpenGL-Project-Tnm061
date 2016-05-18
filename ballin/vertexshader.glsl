#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;
layout(location = 3) in vec3 Tangent;

uniform mat4 MV;
uniform mat4 P;
uniform float time;
uniform vec4 l_pos;

out vec2 stCoords;
out vec3 lightDirection;
out vec4 eyeSpacePos;
out mat3 TBN;
out vec3 lightDistance;

void main(){

    vec4 pos = MV * vec4(Position, 1.0);

  gl_Position = (P * MV) * vec4(Position, 1.0f);
    vec3 T = normalize(vec3(MV * vec4(Tangent,   0.0)));
    vec3 N = normalize(vec3(MV * vec4(Normal,    0.0)));

    T = normalize(T - dot(T, N) * N);

    vec3 B= cross(T,N);

    TBN = mat3(T, B, N);
  stCoords = TexCoord;
  lightDistance = vec3(l_pos - pos);

  lightDirection = normalize(vec3(0.0, 0.5, 1.0));

  //Variable used for calculating fog :)
  eyeSpacePos = -pos;
}
