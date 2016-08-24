#include "Player.h"
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>

Player::Player(const glm::vec3 pos, float limit) :
	Ball(pos, glm::vec4(0.2, 0.2, 0.6, 1), "textures\\frontend-large.bmp"), MOVE_SPEED(5), LIMIT(limit)
{ 
	std::cout << "player: (" << pos.x << "," << pos.y << "," << pos.z << ")" << std::endl;
}

void Player::init() {
	Ball::init();
	_position.y += getSize() / 2;
	_position.z -= getSize() / 2;
}

void Player::move(MovingDirs dir) {
	switch (dir) {
		case MOVE_UP:
			if (_currDirection.z == 0) {
				_currDirection = glm::vec3(0, 0, -1);
			}
			break;
		case MOVE_DOWN:
			if (_currDirection.z == 0) {
				_currDirection = glm::vec3(0, 0, 1);
			}
			break;
		case MOVE_LEFT:
			if (_currDirection.x == 0) {
				_currDirection = glm::vec3(-1, 0, 0);
			}
			break;
		case MOVE_RIGHT:
			if (_currDirection.x == 0) {
				_currDirection = glm::vec3(1, 0, 0);
			}
			break;
		default:
			_currDirection = glm::vec3(0, 0, 0);
			break;
	}
}

GLuint Player::update(float deltaTime) {
	glm::vec3 next = getNextPosition(deltaTime);

	if (isInLimits(next))
		_position = next;
	
	_model = glm::translate(glm::mat4(1), _position);
	// TODO: rotate? (around y axis)
	return 0; 
}

glm::vec3 Player::getNextPosition(float delta) {
	return _position + _currDirection*MOVE_SPEED * delta;
}

bool Player::isInLimits(const glm::vec3 pos) {
	float rad = getSize() / 2;
	return pos.z/* - rad */>= -LIMIT
		&& pos.z/* + rad */<= LIMIT
		&& pos.x/* - rad */>= -LIMIT
		&& pos.x/* + rad */<= LIMIT;
}
