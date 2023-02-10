#version 450 core

layout(binding = 0) uniform sampler2D ColTexture[4];

in vec2 TexCoord;
in float Intensity;

out vec4 FragColor; // Color that will be used for the fragment

/////////////////////////////////////////// ///////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{
    vec4 RED = vec4(1,0,0,1);
    vec2 dist = vec2(0.5,0.5);
    vec4 colour = texture(ColTexture[0], TexCoord.xy);

    vec4 useColour = mix(colour, RED ,distance(TexCoord.xy, dist));

    FragColor = vec4(useColour.xyz * Intensity, 1.0);

//Adds a red damage/death tint over the screen
    
}