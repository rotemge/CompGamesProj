#pragma once
#include "OpenMeshObject.h"
#define MOVE_SPEED 100
class Player :
	public OpenMeshObject
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
	void draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3 camPos, glm::vec3 lightPos, glm::vec4 lightColor);
	GLuint update(int deltaTime);
	void init();
	// movement
	void move(Commands comm);
	const glm::vec3 getPosition() const { return _position; }
private:
	bool _commands[NUM_OF_COMMANDS];
	void movelogic(glm::vec3 dir, float speed, Commands comm);
};

