#pragma once
#include "Object.h"

class FlatObject : public Object
{
public:
	FlatObject(glm::vec3 pos, const char* texture);
	void draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3 camPos, glm::vec3 lightPos, glm::vec4 lightColor);
	GLuint update(int deltaTime);
protected:
	void defineBuffers();
};

