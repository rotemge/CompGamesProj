#include "EnemyBall.h"
#include <glm\gtc\matrix_transform.hpp>

EnemyBall::EnemyBall():
	Ball(glm::vec3(0,0,0), glm::vec4(0.8, 0.4, 0.5, 1), "textures\\frontend-large.bmp")
{
}

void EnemyBall::init() {
	Ball::init();
	float size = getSize();
	_position.y += size / 2;
}

GLuint EnemyBall::update(int deltaTime) { 
	_model = glm::translate(glm::mat4(1), _position);
	return 0; 
}
void EnemyBall::hit(Wall::Direction side){}
