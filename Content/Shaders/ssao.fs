#version 430 core

// Samplers for pre-rendered color, normal and depth
layout (binding = 0) uniform sampler2D sColor;
layout (binding = 1) uniform sampler2D sNormalDepth;

// Final output
layout (location = 0) out vec4 color;

// Various uniforms controling SSAO effect
uniform float ssao_level = 1.0;
uniform float object_level = 1.0;
uniform float ssao_radius = 5.0;
uniform bool weight_by_angle = true;
uniform uint point_count = 8;
uniform bool randomize_points = true;
uniform int sampleRotations = 10;

float getDepth(vec2 samplevec)
{
  vec2 P = gl_FragCoord.xy / textureSize(sNormalDepth, 0);
  return texture2D(sNormalDepth, vec2(P.x + samplevec.x, P.y + samplevec.y)).w;
}

void main(void)
{
    // Get texture position from gl_FragCoord
    vec2 P = gl_FragCoord.xy / textureSize(sNormalDepth, 0);
    // ND = normal and depth
    vec4 ND = textureLod(sNormalDepth, P, 0);
    // Extract normal and depth
    vec3 N = ND.xyz;
    float my_depth = ND.w;

    if(my_depth != 1){
      //Define 5 degrees as radians
      //const float theta = 0.08726646;
      const float theta = 0.1;

      //Define rotation vector
      mat2 rotmat = mat2(cos(theta), sin(theta), -sin(theta), cos(theta));

      // Define starter vectors
      vec2 samplevecs[8];
      samplevecs[0] = vec2(0, -1);
      samplevecs[1] = vec2(-0.71, 0.71);
      samplevecs[2] = vec2(0.71, 0.71);
      samplevecs[3] = vec2(0.71, -0.71);
      samplevecs[4] = vec2(-0.71, -0.71);
      samplevecs[5] = vec2(0, 1);
      samplevecs[6] = vec2(-1, 0);
      samplevecs[7] = vec2(1, 0);

      // Make 1 = 1 pixel
      for (int i = 0; i < 8; i++)
      {
        samplevecs[i] /= textureSize(sNormalDepth, 0);
      }
    
      // Variable to store all of the samples
      float sampleBuffer = 0;

      // Loop for each sample rotation
      for(int n = 0; n < sampleRotations; n++)
      {
        // Loop for each sample vector
        for(int i = 0; i < 8; i++)
        {
          // Store sample depth
          float sampleDepth = getDepth(samplevecs[i]);
          // Add current rotation to the sampleBuffer.

          if(sampleDepth != 1){
          sampleBuffer += sampleDepth;// - (my_depth-sampleDepth);
          }else{
          sampleBuffer += my_depth;
          }
          
          // Scale the current sample vector
          samplevecs[i] += (normalize(samplevecs[i]) / textureSize(sNormalDepth, 0))*.1;
          // Rotate the current sample vector
          samplevecs[i] *= rotmat;
        }      
        }
   
          // Get the average the collected samples 
          float avgDepth = sampleBuffer/(sampleRotations*8);

          // Define occlusion variable
          float occlusion = 0;
       
          // Check if the average depth is lower than the depth at the current position
          if(avgDepth < my_depth)
            occlusion += ((my_depth-avgDepth)*200);

          //Clamp occlusion to avoid black constants
          occlusion = clamp(occlusion,0,0.5);
          
          // Mix in ambient color scaled by SSAO level
          //    color = vec4(texture2D(gl_FragCoord.x,gl_FragCoord.y));
          //color = vec4(vec3(my_depth),1.0);
          //color = vec4(vec3(getDepth(vec2(0,0))),1.0);
          // Base Color output
          color = vec4(texture2D(sColor, P) - occlusion);

        }else{
          color = vec4(texture2D(sColor, P));
        }
        
    color.w = 1.0;
}



