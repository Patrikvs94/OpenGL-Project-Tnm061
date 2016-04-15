// (GLSL) A minimal vertex shader

#version 330 core //directive to the GLSL compiler, tells wich version of the language we are using

// COMMENTED IN CODE uniform float time;
uniform mat4 C;

layout(location = 0) in vec3 Position; //vertex attribute array index 0
layout(location = 1) in vec3 Normal;    //vertex attribute array index 1
layout(location = 2) in vec2 TexCoord;

out vec3 interpolatedNormal; //Output variable (this will be sent to the fragment shader)
out vec2 st;
out vec3 lightDirection;

void main() {

    //Transform (x, y, z) vertex coordinates with a 4x4 matrix T
    gl_Position = vec4(Position, 1.0);

    vec3 transformedNormal = Normal; //Transform normals correctly

    interpolatedNormal = normalize(transformedNormal); //Normalize before sending to fragment shader
    st = TexCoord; //Will also be interpolated across the triangle

    lightDirection = normalize(mat3(C) * vec3(0.0,0.3,1.0)); // OBS!! Weird way to do this??
}
