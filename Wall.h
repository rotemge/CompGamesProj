#pragma once

#include "FlatObject.h"

class Wall : public FlatObject
{
public:
	enum Direction
	{
		HORIZONTAL,
		VERTICAL
	};
	Wall(glm::vec3 center, int size, Direction dir, int pos, int start, int end);
	void init();
private:
	int _size;
	int _start, _end, _pos;
	Direction _dir;
};

