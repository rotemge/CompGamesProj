#include "Wall.h"
#include "globals.h"
#include <glm\gtc\matrix_transform.hpp>
#include <math.h>
#include <iostream>

Wall::Wall(glm::vec3 center, int size, Direction direction, int index, int start, int end, float thickness, bool isTemp) :
	//position is the top left corner
	FlatObject(direction == VERTICAL ?
		center - glm::vec3(size / 2 - index*thickness, 0, size / 2 - start*thickness) :
		center - glm::vec3(size / 2 - start*thickness, 0, size / 2 - index*thickness),
		"textures\\frontend-large.bmp"),
	_start(start), _end(end), _index(index), _dir(direction), THICK(thickness)
{
	setTemp(isTemp);
}

void Wall::init()
{
	FlatObject::init();

	float len = (_end - _start) * THICK;
	glm::vec4 pos(_position, 1);

	//1
	_vertices.push_back(pos);										// 0  position
	_vertices.push_back(glm::vec4(0, 0.5, 0, 0));					// 1  texture coordinates
	if (HORIZONTAL == _dir) {
		_vertices.push_back(glm::vec4(0, 0, -1, 0));				// 2  norm
		//2
		_vertices.push_back(pos + glm::vec4(len, 0, 0, 0));			// 3  position
		_vertices.push_back(glm::vec4(1, 0.5, 0, 0));				// 4  texture coordinates
		_vertices.push_back(glm::vec4(0, 0, -1, 0));				// 5  norm
		//3
		_vertices.push_back(pos + glm::vec4(0, THICK, 0, 0));		// 6  position
		_vertices.push_back(glm::vec4(0, 0, 0, 0));					// 7  texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(0, 1, -1, 0)));// 8  norm
		//4
		_vertices.push_back(pos + glm::vec4(len, THICK, 0, 0));		// 9  position
		_vertices.push_back(glm::vec4(1, 0, 0, 0));					// 10 texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(0, 1, -1, 0)));// 11 norm
		//5
		_vertices.push_back(pos + glm::vec4(0, THICK, THICK, 0));	// 12 position
		_vertices.push_back(glm::vec4(0, 0.5, 0, 0));				// 13 texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(0, 1, 1, 0)));	// 14 norm
		//6
		_vertices.push_back(pos + glm::vec4(len, THICK, THICK, 0));	// 15 position
		_vertices.push_back(glm::vec4(1, 0.5, 0, 0));				// 16 texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(0, 1, 1, 0)));	// 17 norm
		//7
		_vertices.push_back(pos + glm::vec4(0, 0, THICK, 0));		// 18 position
		_vertices.push_back(glm::vec4(0, 0, 0, 0));					// 19 texture coordinates
		_vertices.push_back(glm::vec4(0, 0, 1, 0));					// 20 norm
		//8
		_vertices.push_back(pos + glm::vec4(len, 0, THICK, 0));		// 21 position
		_vertices.push_back(glm::vec4(1, 0, 0, 0));					// 22 texture coordinates
		_vertices.push_back(glm::vec4(0, 0, 1, 0));					// 23 norm
	}else{
		_vertices.push_back(glm::vec4(-1, 0, 0, 0));				// 2  norm
		//2
		_vertices.push_back(pos + glm::vec4(0, 0, len, 0));			// 3  position
		_vertices.push_back(glm::vec4(1, 0.5, 0, 0));				// 4  texture coordinates
		_vertices.push_back(glm::vec4(-1, 0, 0, 0));				// 5  norm
		//3
		_vertices.push_back(pos + glm::vec4(0, THICK, 0, 0));		// 6  position
		_vertices.push_back(glm::vec4(0, 0, 0, 0));					// 7  texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(-1, 1, 0, 0)));// 8  norm
		//4
		_vertices.push_back(pos + glm::vec4(0, THICK, len, 0));		// 9  position
		_vertices.push_back(glm::vec4(1, 0, 0, 0));					// 10 texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(-1, 1, 0, 0)));// 11 norm
		//5
		_vertices.push_back(pos + glm::vec4(THICK, THICK, 0, 0));	// 12 position
		_vertices.push_back(glm::vec4(0, 0.5, 0, 0));				// 13 texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(1, 1, 0, 0)));	// 14 norm
		//6
		_vertices.push_back(pos + glm::vec4(THICK, THICK, len, 0));	// 15 position
		_vertices.push_back(glm::vec4(1, 0.5, 0, 0));				// 16 texture coordinates
		_vertices.push_back(glm::normalize(glm::vec4(1, 1, 0, 0)));	// 17 norm
		//7
		_vertices.push_back(pos + glm::vec4(THICK, 0, 0, 0));		// 18 position
		_vertices.push_back(glm::vec4(0, 0, 0, 0));					// 19 texture coordinates
		_vertices.push_back(glm::vec4(1, 0, 0, 0));					// 20 norm
		//8
		_vertices.push_back(pos + glm::vec4(THICK, 0, len, 0));		// 21 position
		_vertices.push_back(glm::vec4(1, 0, 0, 0));					// 22 texture coordinates
		_vertices.push_back(glm::vec4(1, 0, 0, 0));					// 23 norm
	}

	defineBuffers();
}

bool Wall::hitWithBall(glm::vec3 ball, float rad)
{
	float upper = _vertices.at(0).z;
	float lower = _vertices.at(15).z; // vertex #6
	float left = _vertices.at(0).x;
	float right = _vertices.at(15).x;
	
	if (lower >= ball.z - rad && upper <= ball.z - rad
		&& ball.x >= left && ball.x <= right) {
		return true; // hit from bellow
	}
	if (upper <= ball.z + rad && lower >= ball.z + rad
		&& ball.x >= left && ball.x <= right) {
		return true; // hit from above
	}
	if (right >= ball.x - rad && left <= ball.x - rad
		&& ball.z >= upper && ball.z <= lower) {
		return true; // hit from left
	}
	if (left <= ball.x + rad && right >= ball.x + rad
		&& ball.z >= upper && ball.z <= lower) {
		return true; // hit from right
	}
	return false;
}

bool Wall::gridOverlap(int row, int col) {
	return (HORIZONTAL == _dir && row == _index && col >= _start && col < _end) 
		|| (VERTICAL == _dir && col == _index && row >= _start && row < _end);

}

void Wall::setTemp(bool temp)
{
	_isTemp = temp;
	_color.r = temp ? 0.5 : 1;
	_color.a = temp ? 0.1 : 1;
}
