#include "Wall.h"
#include "globals.h"
#include <glm\gtc\matrix_transform.hpp>
#include <math.h>

Wall::Wall(glm::vec3 center, int size, Direction direction, int index, int start, int end, float thickness) :
	//position is the top left corner
	FlatObject(direction == VERTICAL ?
		center - glm::vec3(size / 2 - index*thickness, 0, size / 2 - start*thickness) :
		center - glm::vec3(size / 2 - start*thickness, 0, size / 2 - index*thickness),
		"textures\\frontend-large.bmp"),
	_start(start), _end(end), _index(index), _dir(direction), THICK(thickness)
{
}

void Wall::init()
{
	Object::init();

	float len = (_end - _start) * THICK;
	glm::vec4 pos(_position, 1);

	//1
	_vertices.push_back(pos);										// position
	_vertices.push_back(glm::vec4(0, 0.5, 0, 0));					// texture coordinates
	if (HORIZONTAL == _dir) {
		_vertices.push_back(glm::vec4(0, 0, -1, 0));				// norm
		//2
		_vertices.push_back(pos + glm::vec4(len, 0, 0, 0));			// position
		_vertices.push_back(glm::vec4(1, 0.5, 0, 0));				// texture coordinates
		_vertices.push_back(glm::vec4(0, 0, -1, 0));				// norm
		//3
		_vertices.push_back(pos + glm::vec4(0, THICK, 0, 0));		// position
		_vertices.push_back(glm::vec4(0, 0, 0, 0));					// texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(0, 1, -1, 0)));// norm
		//4
		_vertices.push_back(pos + glm::vec4(len, THICK, 0, 0));		// position
		_vertices.push_back(glm::vec4(1, 0, 0, 0));					// texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(0, 1, -1, 0)));// norm
		//5
		_vertices.push_back(pos + glm::vec4(0, THICK, THICK, 0));	// position
		_vertices.push_back(glm::vec4(0, 0.5, 0, 0));				// texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(0, 1, 1, 0)));	// norm
		//6
		_vertices.push_back(pos + glm::vec4(len, THICK, THICK, 0));	// position ***************************
		_vertices.push_back(glm::vec4(1, 0.5, 0, 0));				// texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(0, 1, 1, 0)));	// norm
		//7
		_vertices.push_back(pos + glm::vec4(0, 0, THICK, 0));		// position
		_vertices.push_back(glm::vec4(0, 0, 0, 0));					// texture coordinates
		_vertices.push_back(glm::vec4(0, 0, 1, 0));					// norm
		//8
		_vertices.push_back(pos + glm::vec4(len, 0, THICK, 0));		// position
		_vertices.push_back(glm::vec4(1, 0, 0, 0));					// texture coordinates
		_vertices.push_back(glm::vec4(0, 0, 1, 0));					// norm
	}else{
		_vertices.push_back(glm::vec4(-1, 0, 0, 0));				// norm
		//2
		_vertices.push_back(pos + glm::vec4(0, 0, len, 0));			// position
		_vertices.push_back(glm::vec4(1, 0.5, 0, 0));				// texture coordinates
		_vertices.push_back(glm::vec4(-1, 0, 0, 0));				// norm
		//3
		_vertices.push_back(pos + glm::vec4(0, THICK, 0, 0));		// position
		_vertices.push_back(glm::vec4(0, 0, 0, 0));					// texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(-1, 1, 0, 0)));// norm
		//4
		_vertices.push_back(pos + glm::vec4(0, THICK, len, 0));		// position
		_vertices.push_back(glm::vec4(1, 0, 0, 0));					// texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(-1, 1, 0, 0)));// norm
		//5
		_vertices.push_back(pos + glm::vec4(THICK, THICK, 0, 0));	// position
		_vertices.push_back(glm::vec4(0, 0.5, 0, 0));				// texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(1, 1, 0, 0)));	// norm
		//6
		_vertices.push_back(pos + glm::vec4(THICK, THICK, len, 0));	// position
		_vertices.push_back(glm::vec4(1, 0.5, 0, 0));				// texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(1, 1, 0, 0)));	// norm
		//7
		_vertices.push_back(pos + glm::vec4(THICK, 0, 0, 0));		// position
		_vertices.push_back(glm::vec4(0, 0, 0, 0));					// texture coordinates
		_vertices.push_back(glm::vec4(1, 0, 0, 0));					// norm
		//8
		_vertices.push_back(pos + glm::vec4(THICK, 0, len, 0));		// position
		_vertices.push_back(glm::vec4(1, 0, 0, 0));					// texture coordinates
		_vertices.push_back(glm::vec4(1, 0, 0, 0));					// norm
	}

	defineBuffers();
}

bool Wall::hitWithBall(glm::vec3 ball, float rad)
{
	float upper = _vertices.at(0).z;
	float lower = _vertices.at(15).z;
	float left = _vertices.at(0).x;
	float right = _vertices.at(15).x;
	
	if (lower > ball.z - rad && upper < ball.z - rad
		&& ball.x > left && ball.x < right) {
		return true; // hit from bellow
	}
	if (upper < ball.z + rad && lower > ball.z + rad
		&& ball.x > left && ball.x < right) {
		return true; // hit from above
	}
	if (right > ball.x - rad && left < ball.x - rad
		&& ball.z > upper && ball.z < lower) {
		return true; // hit from left
	}
	if (left < ball.x + rad && right > ball.x + rad
		&& ball.z > upper && ball.z < lower) {
		return true; // hit from right
	}
	return false;
}
