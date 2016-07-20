#pragma once
#include "Ball.h"
#include "Wall.h"

class EnemyBall : public Ball
{
public:
	EnemyBall(float limit);
	void init();
	GLuint update(int deltaTime);
	void hit(Wall::Direction side);
private:
	const float MOVE_SPEED;
	const glm::mat4 _scale;
	glm::vec3 _direction;
	float _rotAng;

	glm::vec3 getRandXZ(float low, float high, bool normalized) const;
	void move(glm::mat4 base, glm::vec3 offset);
	void rotate(glm::mat4 base, float angle);
};

