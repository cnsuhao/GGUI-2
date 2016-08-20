#version 430

//Varying variables
in vec2 UV0;
in vec3 normal0;

//uniforms
layout(location = 0) uniform sampler2D	diffuse;
uniform float time;

// Ouput data
out vec4 color;

void main()
{
    color = vec4(0,0,0,1);

    float x = UV0.x;

    //float funcValue = sin((x*25.0-12.5)+time);
    float funcValue = sin((x)+time/2.0);

    funcValue /= 2.0;
    funcValue += 0.5;



    color = vec4(0,1.0-clamp((distance(UV0.y, funcValue)*150.0),0.0,1.0),0,1);

    // OLD DRAWING METHOD
    if(distance(UV0.y, funcValue) <= 0.0025)
    {
      color = vec4((sin(time)+1.0)/2.0,(cos(time)+1.0)/2.0,0,1);
    }


}
