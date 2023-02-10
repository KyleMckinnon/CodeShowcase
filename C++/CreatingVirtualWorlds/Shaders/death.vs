#version 450 core

layout (location = 0) in vec3               vertexPos_VS;	  	// Position in attribute location 0
layout (location = 1) in vec2               texCoord_VS;
layout (location = 2) in vec3               vertexNormal_VS;

layout (location = 3) uniform mat4          modelMatrix;
layout (location = 4) uniform mat4          viewMatrix;
layout (location = 5) uniform mat4          projMatrix;
layout (location = 6) uniform int			numLights;
layout (location = 7) uniform vec3			LightPos[2];

out vec2 TexCoord;
out float Intensity;

//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{    
    TexCoord    = texCoord_VS;
	vec4 m_pos = modelMatrix * vec4(vertexPos_VS, 1.0);
	vec3 n = vec3(mat3(modelMatrix) * vertexNormal_VS);
	n = normalize(n);

	Intensity = 0.0;

	for ( int i =0; i<numLights; i++)
	{
	vec3 light = vec3(LightPos[0].xyz);
	vec3 lv = light - vec3(m_pos.xyz);
	float d = length(lv);
	lv = normalize(lv);

	Intensity += clamp(dot(n,lv), 0.0, 1.0);

	}

	Intensity = clamp(Intensity, 0.0, 1.0);
	
	

    gl_Position   = (projMatrix * viewMatrix * modelMatrix * vec4(vertexPos_VS, 1.0));
}