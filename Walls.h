#pragma once

#include "FlatObject.h"

class Walls : public FlatObject
{
public:
	enum Direction
	{
		HORIZONTAL,
		VERTICAL
	};
	Walls(glm::vec3 center, float size, float rot);
	void init();
private:
	float _size;
	int _start, _end;
	Direction _dir;
};

