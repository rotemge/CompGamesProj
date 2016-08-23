#include "FlatObject.h"
#include "globals.h"


FlatObject::FlatObject(glm::vec3 pos, const char* texture) : 
	Object("shaders\\phong_regular.vert", "shaders\\phong.frag", pos, glm::vec4(1, 1, 1, 1), texture)
{
}

void FlatObject::draw(const glm::mat4 & projection, const glm::mat4& view, const glm::vec3 camPos, glm::vec3 lightPos, glm::vec4 lightColor)
{
	BEGIN_OPENGL;
	{
		_useMVP(projection, view);
		_setWorldUniforms(camPos, lightPos, lightColor);

		// Get a handle for our "gMaterialColor" uniform
		GLuint materialID = getUniformLocation(MATERIAL_COLOR);
		glUniform4f(materialID, _color.r, _color.g, _color.b, _color.a);

		glUniform1i(getUniformLocation(TEXTURE_SAMPLER), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _textureID);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(_vao);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, _vertices.size());
		glBindVertexArray(0);
	}
	END_OPENGL;
}

void FlatObject::defineBuffers() {
	// Create and bind the object's Vertex Array Object
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// Create and load vertex data into a Vertex Buffer Object
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(glm::vec4) * _vertices.size(),
		&_vertices[0],
		GL_STATIC_DRAW);

	// Tells OpenGL that there is vertex data in this buffer object and what form that vertex data takes:
	// Obtain attribute handles:
	GLint posAttr = glGetAttribLocation(_programID, "position");
	glEnableVertexAttribArray(posAttr);
	glVertexAttribPointer(posAttr, // attribute handle
		4,          // number of scalars per vertex
		GL_FLOAT,   // scalar type
		GL_FALSE,
		sizeof(glm::vec4) * 3,
		0);

	GLint texAttr = glGetAttribLocation(_programID, "texCoord");
	glEnableVertexAttribArray(texAttr);
	glVertexAttribPointer(texAttr, // attribute handle
		4,          // number of scalars per vertex
		GL_FLOAT,   // scalar type
		GL_FALSE,
		sizeof(glm::vec4) * 3,
		(GLvoid*)(sizeof(glm::vec4)));

	GLint normAttr = glGetAttribLocation(_programID, "norm");
	glEnableVertexAttribArray(normAttr);
	glVertexAttribPointer(normAttr,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec4) * 3,
		(GLvoid*)(sizeof(glm::vec4) * 2));


	// Unbind vertex array:
	glBindVertexArray(0);
}

GLuint FlatObject::update(int deltaTime) { return 0; }
