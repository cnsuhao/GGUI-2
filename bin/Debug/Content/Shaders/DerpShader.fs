#version 430

//Varying variables
in vec2 UV0;
in vec3 normal0;

//uniforms
uniform float Opacity;

// Textures
uniform sampler2D diffuse;

// Input data
//in vec3 positionWorld;

// Ouput data
layout(location = 0) out vec4 color;

void main()
{
  
  // Output color
  color =
      texture2D(diffuse, UV0) // base color / texture
      * Opacity; // Opacity application
  
  // Definition of constant values
  const double minval = 0.0025;
  const double maxval = 0.9975;
  /*
  //Check if outside UV Range
  if(UV0.x >= maxval) color.w = 0.0;
  if(UV0.x <= minval) color.w = 0.0;
  if(UV0.y >= maxval) color.w = 0.0;
  if(UV0.y <= minval) color.w = 0.0;
  */
  //gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);

  //gl_FragColor = texture2D(diffuse, UV0);
  //gl_FragColor = vec4(0,0,0,1.0);
}
