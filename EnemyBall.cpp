#include "EnemyBall.h"
#include <glm\gtc\matrix_transform.hpp>
#include <cstdlib>

EnemyBall::EnemyBall(float limit) :
	Ball(glm::vec3(0,0,0), glm::vec4(0.8, 0.4, 0.5, 1), "textures\\black-white-stripes.bmp"),
	_limit(limit), MOVE_SPEED(3.f), _scaleFactor(1), //_scale(glm::scale(glm::mat4(1), glm::vec3(0.7, 0.7, 0.7))),
	_direction(getRandXZ(-1, 1, true)), _rotAng(0)
{
}

void EnemyBall::init() {
	Ball::init();
	float lim = _limit - getRadius()*2;
	_position = getRandXZ(-lim, lim, false);
	_position.y += getRadius();
}
GLuint EnemyBall::update(float deltaTime) {
	float speed = MOVE_SPEED * deltaTime;
	glm::vec3 offset(_direction * speed);

	move(_scale, offset);
	// angle = (arc length) / radius
	rotate(_model, -glm::length(offset) / getRadius());
	
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
