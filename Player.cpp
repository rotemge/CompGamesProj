#include "Player.h"
#include <glm\gtc\matrix_transform.hpp>

Player::Player(const glm::vec3 pos) :
	Ball(pos, glm::vec4(0.2, 0.2, 0.6, 1), "textures\\frontend-large.bmp"), MOVE_SPEED(100)
{ }

void Player::init() {
	Ball::init();
	_position.y += getSize() / 2;
	_position.z -= getSize() / 2;
}

void Player::move(Commands comm) { _commands[comm] = true; }

void Player::movelogic(glm::vec3 dir, float speed, Commands comm)
{
	_commands[comm] = false;
	_position += dir*speed;
}

GLuint Player::update(int deltaTime) { 
	float delta = deltaTime * 0.001f;
	float speed = MOVE_SPEED * delta;

	if (_commands[MOVE_UP]) { movelogic(glm::vec3(0, 0, -1), speed, Commands::MOVE_UP); }
	if (_commands[MOVE_DOWN]) { movelogic(glm::vec3(0, 0, 1), speed, Commands::MOVE_DOWN); }
	if (_commands[MOVE_RIGHT]) { movelogic(glm::vec3(1, 0, 0), speed, Commands::MOVE_RIGHT); }
	if (_commands[MOVE_LEFT]) { movelogic(glm::vec3(-1, 0, 0), speed, Commands::MOVE_LEFT); }
	_model = glm::translate(glm::mat4(1), _position);
	// TODO: rotate? (around y axis)
	return 0; 
}
