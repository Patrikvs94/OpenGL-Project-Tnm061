#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;

uniform mat4 MV;
uniform mat4 P;
uniform float time;

out vec3 interpolatedNormal;
out vec2 stCoords;
out vec3 lightDirection;
out vec4 eyeSpacePos;

void main(){

  gl_Position = (P * MV) * vec4(Position, 1.0f);
  interpolatedNormal = mat3(MV) * Normal;
  stCoords = TexCoord;

  lightDirection = normalize(vec3(0.0, 0.5, 1.0));

  //Variable used for calculating fog :)
  eyeSpacePos = MV * vec4(Position, 1.0);
}
