#version 410
//precision highp float;

//Varying variables
in vec2 UV0;
in vec3 normal0;

//uniforms
uniform float Opacity;
uniform vec3 FillColor;

//Font rendering
uniform bool FontRendering;
uniform float TextureWidth;
uniform float TextureHeight;
uniform float FontX;
uniform float FontY;
uniform float FontWidth;
uniform float FontHeight;


// Textures
uniform sampler2D diffuse;

// Ouput data
out vec4 color;

#define minval 0.0025
#define maxval 0.9975

void main()
{
  
  if (FontRendering)
  {
    //char id=33 x=493 y=142 width=11 height=38 xoffset=0 yoffset=6 xadvance=12 page=0 chnl=15
    //float minX = FontX/TextureWidth;
    //float maxX = (FontX+FontWidth)/TextureWidth;
    //float minY = FontY/TextureHeight;
    //float maxY = (FontY+FontHeight)/TextureHeight;

    //vec2 fontUV = vec2(mix(minX, maxX, UV0.x), mix(minY, maxY, UV0.y));
    vec2 fontUV = vec2(
      mix(FontX / TextureWidth, (FontX+FontWidth)/TextureWidth, UV0.x), 
      mix(FontY / TextureHeight, (FontY+FontHeight)/TextureHeight, UV0.y)
      );
    //char id=101 x=0 y=453 width=24 height=27 xoffset=-2 yoffset=18 xadvance=19 page=0 chnl=15


    color =
      texture(diffuse, fontUV) // base color / texture
      * Opacity; // Opacity application

       //Color using fill color
    color.xyz *= FillColor;
    
    //color.w = 1.0;
    //color.xyz = vec3(0);
    //color.x = TextureWidth/512.0f;
  }else{
     // Output color
    color =
      texture(diffuse, UV0) // base color / texture
      * Opacity; // Opacity application


    //Color using fill color
    color.xyz *= FillColor;
  }


}
