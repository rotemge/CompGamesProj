#pragma once
#include "OpenMeshObject.h"
class Ball :
	public OpenMeshObject
{
public:
	Ball(const glm::vec3 pos, const glm::vec4 color, const char* texture);
	void draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3 camPos, glm::vec3 lightPos, glm::vec4 lightColor);
	void init();
};

