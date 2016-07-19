#include "Ball.h"
#include "globals.h"

Ball::Ball(const glm::vec3 pos, const glm::vec4 color, const char* texture) :
	OpenMeshObject("shaders\\spherical.vert", "shaders\\simple.frag", pos, color, "meshes\\sphere.obj", texture)
{
}

void Ball::init() {
	OpenMeshObject::init();

	// Initialize vertices buffer and transfer it to OpenGL
	{
		// Create and bind the Mesh Vertex Array Object
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		// Create and load vertex data into a Vertex Buffer Object
		{
			glGenBuffers(1, &_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER,
				sizeof(glm::vec4) * _vertices.size(),
				&_vertices[0],
				GL_STATIC_DRAW);

			// Obtain attribute handles:
			GLint _posAttr = glGetAttribLocation(_programID, "position");
			glEnableVertexAttribArray(_posAttr);
			glVertexAttribPointer(_posAttr, // attribute handle
				4,          // number of scalars per vertex
				GL_FLOAT,   // scalar type
				GL_FALSE,
				sizeof(glm::vec4),
				0);

			// Unbind vertex array:
			glBindVertexArray(0);
		}
	}
}

void Ball::draw(const glm::mat4 & projection, const glm::mat4& view, const glm::vec3 camPos, glm::vec3 lightPos, glm::vec4 lightColor)
{
	BEGIN_OPENGL;
	{
		_useMVP(projection, view);
		_setWorldUniforms(camPos, lightPos, lightColor);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(_vao);

		// Get a handle for our "gMaterialColor" uniform
		GLuint materialID = getUniformLocation(MATERIAL_COLOR);
		glUniform4f(materialID, _color.r, _color.g, _color.b, _color.a);

		GLuint textureSamplerID = getUniformLocation(TEXTURE_SAMPLER);
		glUniform1i(textureSamplerID, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _textureID);

		//draw
		glDrawArrays(GL_TRIANGLES, 0, _vertices.size());

		// Unbind the Vertex Array object
		glBindVertexArray(0);
	}
	END_OPENGL;
}
