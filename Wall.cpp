#include "Wall.h"
#include "globals.h"
#include <glm\gtc\matrix_transform.hpp>
#include <math.h>
#include <iostream>

#define CONV(x,y) (x + (_size / 2 - y)) / (_size)

Wall::Wall(glm::vec3 center, int size, Direction direction, int index, int start, int end, float thickness, bool isTemp) :
	//position is the top left corner
	FlatObject(direction == VERTICAL ?
		center - glm::vec3(size / 2 - index*thickness, 0, size / 2 - start*thickness) :
		center - glm::vec3(size / 2 - start*thickness, 0, size / 2 - index*thickness),
		"textures\\marble.bmp", glm::vec4(1, 1, 1, 1)),
	_start(start), _end(end), _index(index), _size(size), _dir(direction), THICK(thickness), _center(center)
{
	setTemp(isTemp);
}

glm::vec4 Wall::posToTexCoor(glm::vec4 pos) {
	// -10,-10 => 0,0   => 0,0
	//  10, 10 => 20,20 => 1,1
	return glm::vec4(CONV(pos.x, _center.x), CONV(pos.z, _center.z), 0, 0);
}

void Wall::init()
{
	FlatObject::init();

	float len = (_end - _start) * THICK;
	float right = (HORIZONTAL == _dir ? len : THICK);
	float front = (HORIZONTAL == _dir ? THICK : len);

	glm::vec4 A(_position, 1);
	glm::vec4 B = A + glm::vec4(0, THICK, 0, 0);
	glm::vec4 C = B + glm::vec4(0, 0, front, 0);
	glm::vec4 D = A + glm::vec4(0, 0, front, 0); 
	glm::vec4 E = D + glm::vec4(right, 0, 0, 0);
	glm::vec4 F = C + glm::vec4(right, 0, 0, 0);
	glm::vec4 H = A + glm::vec4(right, 0, 0, 0);
	glm::vec4 G = B + glm::vec4(right, 0, 0, 0);

	//left face
	_vertices.push_back(A);							// 0  position
	_vertices.push_back(glm::vec4(0, 0.5, 0, 0));	// 1  texture coordinates
	_vertices.push_back(glm::vec4(-1, 0, 0, 0));	// 2  normal
	_vertices.push_back(B);							// 3  position
	_vertices.push_back(glm::vec4(0, 0, 0, 0));		// 4  texture coordinates
	_vertices.push_back(glm::vec4(-1, 0, 0, 0));	// 5  normal
	_vertices.push_back(C);							// 6  position
	_vertices.push_back(glm::vec4(1, 0, 0, 0));		// 7  texture coordinates
	_vertices.push_back(glm::vec4(-1, 0, 0, 0));	// 8  normal
	_vertices.push_back(D);							// 9  position
	_vertices.push_back(glm::vec4(1, 0.5, 0, 0));	// 10 texture coordinates
	_vertices.push_back(glm::vec4(-1, 0, 0, 0));	// 11 normal
	//right face
	_vertices.push_back(H);							// 12  position
	_vertices.push_back(glm::vec4(1, 0.5, 0, 0));	// 13  texture coordinates
	_vertices.push_back(glm::vec4(1, 0, 0, 0));		// 14  normal
	_vertices.push_back(G);							// 15  position
	_vertices.push_back(glm::vec4(1, 0, 0, 0));		// 16  texture coordinates
	_vertices.push_back(glm::vec4(1, 0, 0, 0));		// 17  normal
	_vertices.push_back(F);							// 18  position
	_vertices.push_back(glm::vec4(0, 0, 0, 0));		// 19  texture coordinates
	_vertices.push_back(glm::vec4(1, 0, 0, 0));		// 20  normal
	_vertices.push_back(E);							// 21  position
	_vertices.push_back(glm::vec4(0, 0.5, 0, 0));	// 22  texture coordinates
	_vertices.push_back(glm::vec4(1, 0, 0, 0));		// 23  normal
	//front face
	_vertices.push_back(C);							// 24  position
	_vertices.push_back(glm::vec4(0, 0.5, 0, 0));	// 25  texture coordinates
	_vertices.push_back(glm::vec4(0, 0, 1, 0));		// 26  normal
	_vertices.push_back(D);							// 27  position
	_vertices.push_back(glm::vec4(0, 0, 0, 0));		// 28  texture coordinates
	_vertices.push_back(glm::vec4(0, 0, 1, 0));		// 29  normal
	_vertices.push_back(E);							// 30  position
	_vertices.push_back(glm::vec4(1, 0, 0, 0));		// 31  texture coordinates
	_vertices.push_back(glm::vec4(0, 0, 1, 0));		// 32  normal
	_vertices.push_back(F);							// 33  position
	_vertices.push_back(glm::vec4(1, 0.5, 0, 0));	// 34 texture coordinates
	_vertices.push_back(glm::vec4(0, 0, 1, 0));		// 35  normal
	//up face
	_vertices.push_back(B);							// 36  position
	_vertices.push_back(posToTexCoor(B));			// 37  texture coordinates
	_vertices.push_back(glm::vec4(0, 1, 0, 0));		// 38  normal
	_vertices.push_back(C);							// 39  position
	_vertices.push_back(posToTexCoor(C));			// 40  texture coordinates
	_vertices.push_back(glm::vec4(0, 1, 0, 0));		// 41  normal
	_vertices.push_back(F);							// 42  position
	_vertices.push_back(posToTexCoor(F));			// 43  texture coordinates
	_vertices.push_back(glm::vec4(0, 1, 0, 0));		// 44  normal
	_vertices.push_back(G);							// 45  position
	_vertices.push_back(posToTexCoor(G));			// 46  texture coordinates
	_vertices.push_back(glm::vec4(0, 1, 0, 0));		// 47  normal
	
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
//		std::cout << "DEBUG :: hit from bellow" << std::endl;
		return true; // hit from bellow
	}
	if (upper <= ball.z + rad && lower >= ball.z + rad
		&& ball.x >= left && ball.x <= right) {
//		std::cout << "DEBUG :: hit from above" << std::endl;
		return true; // hit from above
	}
	if (right >= ball.x - rad && left <= ball.x - rad
		&& ball.z >= upper && ball.z <= lower) {
//		std::cout << "DEBUG :: hit from the left" << std::endl;
		return true; // hit from left
	}
	if (left <= ball.x + rad && right >= ball.x + rad
		&& ball.z >= upper && ball.z <= lower) {
//		std::cout << "DEBUG :: hit from the right" << std::endl;
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
	_color.r = temp ? 0.5f : 1;
	_color.a = temp ? 0.1f : 1;
}
