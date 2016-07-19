#pragma once
#include "Ball.h"
#include "Wall.h"

class EnemyBall :
	public Ball
{
public:
	EnemyBall();
	void init();
	GLuint update(int deltaTime);
	void hit(Wall::Direction side);
private:
	glm::vec3 _direction;
};

