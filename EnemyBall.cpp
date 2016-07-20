#include "EnemyBall.h"
#include <glm\gtc\matrix_transform.hpp>
#include <cstdlib>

EnemyBall::EnemyBall(float limit) :
	Ball(getRandXZ(-limit, limit, false), glm::vec4(0.8, 0.4, 0.5, 1), "textures\\black-white-stripes.bmp"),
	MOVE_SPEED(1.f), _scale(glm::scale(glm::mat4(1), glm::vec3(0.7, 0.7, 0.7))), 
	_direction(getRandXZ(-1, 1, true)), _rotAng(0)
{
}

void EnemyBall::init() {
	Ball::init();
	float size = getSize();
	_position.y += size / 2;
}
GLuint EnemyBall::update(int deltaTime) {
	float delta = deltaTime * 0.001f;
	float speed = MOVE_SPEED * delta;
	glm::vec3 offset(_direction * speed);

	move(_scale, offset);
	// angle = (arc length) / radius
	rotate(_model, -glm::length(offset) / (getSize() / 2));
	
	return 0; 
}

void EnemyBall::move(glm::mat4 base, glm::vec3 offset) {
	_position += offset;
	_model = glm::translate(base, _position);
}

void EnemyBall::rotate(glm::mat4 base, float angle) {
	_rotAng += angle;
	glm::vec3 axis(glm::cross(_direction, glm::vec3(0, 1, 0)));
	_model = glm::rotate(base, _rotAng, axis);
}

void EnemyBall::hit(Wall::Direction side){
	if (Wall::HORIZONTAL == side) {
		_direction.z = -_direction.z;
	}
	else {
		_direction.x = -_direction.x;
	}
}
 
glm::vec3 EnemyBall::getRandXZ(float low, float high, bool normalized) const {
	float rx = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	float rz = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	glm::vec3 res(rx, 0, rz);
	if (normalized) {
		res = glm::normalize(res);
	}
	return res;
}
