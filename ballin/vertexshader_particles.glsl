#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;
layout(location = 3) in vec3 Color;

uniform mat4 MV;
uniform mat4 P;
uniform float time;

out vec2 stCoords;
out vec3 lightDirection;
out vec3 interpolatedNormal;
out vec4 eyeSpacePos;
out vec3 interpolatedColor;

void main(){

  gl_Position = (P * MV) * vec4(Position, 1.0f);
    interpolatedNormal = normalize(vec3(MV * vec4(Normal,    0.0)));

  stCoords = TexCoord;
    interpolatedColor = Color;
    interpolatedColor = vec3(1.0,1.0,1.0);
  lightDirection = normalize(vec3(0.0, 0.5, 1.0));

  //Variable used for calculating fog :)
  eyeSpacePos = MV * vec4(Position, 1.0);
}
