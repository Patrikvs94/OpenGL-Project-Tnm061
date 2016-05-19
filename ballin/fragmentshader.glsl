#version 330 core

uniform float time;
uniform sampler2D tex;
uniform sampler2D norm;

in vec2 stCoords;
in vec3 lightDirection;
in mat3 TBN;
in float t;
out vec4 outputColor;

/* Testing linear fog */
in vec4 eyeSpacePos;

void main() {

    vec3 interpolatedNormal=normalize( vec3(texture(norm, stCoords)));
    interpolatedNormal=normalize(interpolatedNormal * 2.0 - 1.0);
    interpolatedNormal=normalize(TBN*interpolatedNormal);
    vec4 emission = vec4(0.0, 0.0, 0.0, 0.0);

    //Fog parameters (should be uniforms.....)
    //vec4 vFogColor = vec4(0.7*sin(time), 0.7*sin(time*0.5), 0.7*cos(2*time), 1.0f); //Should be the same as the background
    vec4 vFogColor = vec4(0.4, 0.4, 0.4, 1.0);
    float fStart = 25.0f;
    float fEnd = 50.0f;

//    ///Create diffuse shading
//    vec4 texcolor = texture(tex, stCoords);
//    vec3 nNormal = normalize(interpolatedNormal);
//    float diffuse = max(0.0, nNormal.z);
//
//    outputColor = texcolor * diffuse;

    //Create specular shading (assumes that interpolatedNormal, lightDirection and V are normalized)
    vec3 ka = vec3(0.5, 0.5, 0.5);          // ambient reflection color
    vec3 Ia = vec3(0.2, 0.2, 0.2);          // ambient illumination color
    vec3 kd = vec3(texture(tex, stCoords));   // diffuse surface reflection color
    vec3 Id = vec3(1.0, 1.0, 1.0);          // diffuse illumination color
    vec3 ks = vec3(1.0, 1.0, 1.0);          // specular surface reflection color
    vec3 Is = vec3(0.3, 0.3, 0.3);          // specular illumination color
    float n = 10;                           // the "shininess" parameter

    vec3 V = vec3(0.0, 0.0, 1.0);       //Direction of the viewer. ALWAYS (0,0,1)!
    if(kd[2]>0.99)
    {
        emission= vec4(1.0, 1.0, 1.0, 0.0)*abs(sin(2.0*t));
    }
    else if(kd[2]>0.65)
    {
        emission= vec4(0.4, 0.4, 0.4, 0.0)*abs(sin(0.5*t));
    }
    vec3 R = 2.0*dot(interpolatedNormal, lightDirection)*interpolatedNormal - lightDirection; //Could also use the function reflect();   // R is the computed reflection direction

    float dotNL = max(dot(interpolatedNormal, lightDirection), 0.0);  // Scalar product between light direction and normal. If negative, set to zero.
    float dotRV = max(dot(R,V), 0.0);                           //Scalar product between computed reflection direction and view direction
    if (dotNL == 0.0) dotRV = 0.0;                              //Do not show highlight on the dark side

    vec3 shadedcolor = Ia*ka + Id*kd*dotNL + Is*ks*pow(dotRV, n);   //Final color (for each pixel)
    outputColor = vec4(shadedcolor, 1.0); //Using colors for surface colors

    //Add fog
    float fFogCoord = abs(eyeSpacePos.z/eyeSpacePos.w);
    float fogFactor = 1 - clamp((fEnd-fFogCoord)/(fEnd-fStart), 0.0, 1.0); //Calculate the fog factor (uses a LINEAR equation)

    outputColor = emission + mix(outputColor, vFogColor, fogFactor);   //Create output color by "mixing" (interpolate)
                                                            //the fog with the color using the chosen fog factor
}
