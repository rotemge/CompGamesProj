#pragma once
#include "Ball.h"

class Player :
	public Ball
{
public:
	enum MovingDirs
	{
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_NONE
	};

	Player(const glm::vec3 pos, float limit);
	void init();
	GLuint update(float deltaTime);
	// movement
	void move(MovingDirs dir);
	glm::vec3 getNextPosition(float speed);
	void resetPos(glm::vec3 pos);
	bool isMoving();
private:
	const float MOVE_SPEED;
	const float LIMIT;
	glm::vec3 _currDirection;
	bool isInLimits(const glm::vec3 pos);
};

