#pragma once

#include "ShadedObject.h"
#include <glm/glm.hpp> //glm::vec3
#include <vector>

#define MATERIAL_COLOR "gMaterialColor"

class Object : public ShadedObject
{
public:
	Object(const char* vShaderFile,
		const char* fShaderFile,
		const glm::vec3 & position,
		const glm::vec4 & color,
		const char* textureIMG);
	virtual ~Object() {};

	// Updates the object's params if needed (does in each render frame)
	virtual GLuint update(int deltaTime) = 0;
	virtual void draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3 camPos, glm::vec3 lightPos, glm::vec4 lightColor) = 0;

	// Draws the object
	virtual void init() {
		ShadedObject::init();
		addShader(GL_VERTEX_SHADER, _vShaderFile);
		addShader(GL_FRAGMENT_SHADER, _fShaderFile);
		finalize();
	}

	glm::mat4 getModel() { return _model; }
	const glm::vec3 getPosition() const { return _position; }

protected:
	glm::vec3 _position;
	glm::vec4 _color;
	glm::vec3 _speed;
	// Shaders' stuff
	GLuint _vao, _vbo, _ebo;
	const char* _vShaderFile;
	const char* _fShaderFile;
	// MVP
	glm::mat4 _model;	

	std::vector<glm::vec4> _vertices;

	void _useMVP(const glm::mat4& projection, const glm::mat4& view);
	void _setWorldUniforms(const glm::vec3 camPos, glm::vec3 lightPos, glm::vec4 lightColor);
	void _setPosition(const glm::vec4& pos) { _position = glm::vec3(pos); }
	void _setPosition(const glm::vec3& pos) { _position = pos; }
};

