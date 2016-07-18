#include "Object.h"


Object::Object(const char* vShaderFile, const char* fShaderFile,
	const glm::vec3 & position, const glm::vec4 & color, const char* textureIMG) :
	ShadedObject(textureIMG), _vShaderFile(vShaderFile), _fShaderFile(fShaderFile), _position(position), _color(color)
{
}

void Object::_useMVP(const glm::mat4 & projection, const glm::mat4 & view)
{
	// Get a handle for our "gProjection" uniform
	GLuint projectionMatrixID = getUniformLocation("gProjection");
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projection[0][0]);
	// Get a handle for our "gView" uniform
	GLuint viewMatrixID = getUniformLocation("gView");
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &view[0][0]);
	// Get a handle for our "gModel" uniform
	GLuint modelMatrixID = getUniformLocation("gModel");
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &_model[0][0]);
}


void Object::_setWorldUniforms(const glm::vec3 camPos, glm::vec3 lightPos, glm::vec4 lightColor)
{
	GLuint cameraID = getUniformLocation("gEyePosition");
	glUniform3f(cameraID, camPos.x, camPos.y, camPos.z);

	GLuint lightPosID = getUniformLocation("gLightPosition");
	glUniform4f(lightPosID, lightPos.x, lightPos.y, lightPos.z, 1);

	GLuint lightColorID = getUniformLocation("gLightColor");
	glUniform4f(lightColorID, lightColor.r, lightColor.g, lightColor.b, 1);
}
