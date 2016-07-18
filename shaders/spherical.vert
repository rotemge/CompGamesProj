#version 330 core

#define MY_PI 3.1415926
layout(location = 0) in vec4 position;

// Output data will be interpolated for each fragment.
out vec2 TexCoordPass;

// Values that stay constant for the whole mesh.
uniform mat4 gModel, gView, gProjection;

void main()
{
	mat4 MVP = gProjection * gView * gModel;
	
	// Output position of the vertex, in clip space : gMVP * position
	gl_Position =  MVP * position;

	// Set texture coordinates using spherical mapping:
    {
    	float theta = atan(position.x/position.z);
    	float phi   = atan(position.y/length(vec2(position.x,position.z)));
    	float r     = length(position.xyz);
    	TexCoordPass.x = 1.0 - (theta + MY_PI) / (2*MY_PI);
    	TexCoordPass.y = 1.0 - (phi + MY_PI/2)  / MY_PI;
    }
}