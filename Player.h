#pragma once
#include "Ball.h"

#define MOVE_SPEED 100

class Player :
	public Ball
{
public:
	enum Commands
	{
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		NUM_OF_COMMANDS
	};

	Player(const glm::vec3 pos);
	void init();
	GLuint update(int deltaTime);	
	// movement
	void move(Commands comm);
private:
	bool _commands[NUM_OF_COMMANDS];
	void movelogic(glm::vec3 dir, float speed, Commands comm);
};

