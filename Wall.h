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
	Wall(glm::vec3 center, int size, Direction dir, int index, int start, int end, float thickness);
	void init();
private:
	const int _start, _end, _index;
	const Direction _dir;
	const float THICK;
};

