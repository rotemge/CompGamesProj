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
	Wall(glm::vec3 center, int size, Direction dir, int index, int start, int end, float thickness, bool isTemp);
	void init();
	const float getThickness() const { return THICK; }
	const Direction getDirection() const { return _dir; }
	const bool isTemp() const { return _isTemp; }
	bool hitWithBall(glm::vec3 pos, float rad);
private:
	const int _start, _end, _index;
	const Direction _dir;
	const float THICK;
	bool _isTemp;
};

