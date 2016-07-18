#version 330 core

#define MY_PI 3.1415926
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 texCoord;

// Output data will be interpolated for each fragment.
out vec2 TexCoordPass;

// Values that stay constant for the whole mesh.
uniform mat4 gModel, gView, gProjection;

void main()
{
	mat4 MVP = gProjection * gView * gModel;
	
	// Output position of the vertex, in clip space : gMVP * position
	gl_Position =  MVP * position;

	TexCoordPass = texCoord.xy;
}