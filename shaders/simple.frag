#version 330 core

// Interpolated values from the vertex shaders
in vec2 TexCoordPass;
// Ouput data
out vec3 outColor;

// Values that stay constant for the whole mesh.
uniform sampler2D gTextureSampler;
uniform vec4 gMaterialColor;
uniform vec4 gLightColor;

void main()
{
	vec3 LightColor = gLightColor.rgb;	
	// Material properties
	vec3 materialDiffuseColor = texture2D(gTextureSampler, TexCoordPass).rgb * gMaterialColor.xyz;	
	outColor = materialDiffuseColor * LightColor;	
}