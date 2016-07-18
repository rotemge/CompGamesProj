#pragma once

#include "FlatObject.h"

class Floor : public FlatObject
{
public:
	Floor(glm::vec3 center, float size);
	void init();
private:
	float _width;
	float _height;
};

