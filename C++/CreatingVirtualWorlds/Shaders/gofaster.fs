#version 450 core

layout(binding = 0) uniform sampler2D ColTexture[4];

in vec2 TexCoord;
in float Intensity;
in float y_pos;

out vec4 FragColor; // Color that will be used for the fragment

/////////////////////////////////////////// ///////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{
    
    vec4 colour = texture(ColTexture[0], TexCoord.xy);

    vec3 col = colour.xyz * Intensity;

    if(y_pos > -0.1 && y_pos < 0.1)
    col = vec3(0.3, 0.9, 1.0);

    FragColor = vec4(vec3(col), 1.0);

//Adds a go fast line through the middle of the object the shader is applied to
}