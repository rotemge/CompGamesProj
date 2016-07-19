#include "Wall.h"
#include "globals.h"
#include <glm\gtc\matrix_transform.hpp>
#include <math.h>

Wall::Wall(glm::vec3 center, int size, Direction direction, int index, int start, int end, float thickness) :
	//position is the top left corner
	FlatObject(direction == VERTICAL ?
		center - glm::vec3(size / 2 - index*thickness, 0, size / 2 - start*thickness) :
		center - glm::vec3(size / 2 - start*thickness, 0, size / 2 - index*thickness),
		"textures\\marble.bmp"),
	_start(start), _end(end), _index(index), _dir(direction), THICK(thickness)
{
}

void Wall::init()
{
	Object::init();

	float len = (_end - _start) * THICK;
	glm::vec4 pos(_position, 1);

	//1
	_vertices.push_back(pos);										//position
	_vertices.push_back(glm::vec4(0, 0.5, 0, 0));					// texture coordinates
	if (HORIZONTAL == _dir) {
		//2
		_vertices.push_back(pos + glm::vec4(len, 0, 0, 0));			//position
		_vertices.push_back(glm::vec4(1, 0.5, 0, 0));
		//3
		_vertices.push_back(pos + glm::vec4(0, THICK, 0, 0));		//position
		_vertices.push_back(glm::vec4(0, 0, 0, 0));
		//4
		_vertices.push_back(pos + glm::vec4(len, THICK, 0, 0));		//position
		_vertices.push_back(glm::vec4(1, 0, 0, 0));
		//5
		_vertices.push_back(pos + glm::vec4(0, THICK, THICK, 0));	//position
		_vertices.push_back(glm::vec4(0, 0.5, 0, 0));
		//6
		_vertices.push_back(pos + glm::vec4(len, THICK, THICK, 0));	//position
		_vertices.push_back(glm::vec4(1, 0.5, 0, 0));
		//7
		_vertices.push_back(pos + glm::vec4(0, 0, THICK, 0));		//position
		_vertices.push_back(glm::vec4(0, 0, 0, 0));
		//8
		_vertices.push_back(pos + glm::vec4(len, 0, THICK, 0));		//position
		_vertices.push_back(glm::vec4(1, 0, 0, 0));
	}else{
		//2
		_vertices.push_back(pos + glm::vec4(0, 0, len, 0));			//position
		_vertices.push_back(glm::vec4(1, 0.5, 0, 0));
		//3
		_vertices.push_back(pos + glm::vec4(0, THICK, 0, 0));		//position
		_vertices.push_back(glm::vec4(0, 0, 0, 0));
		//4
		_vertices.push_back(pos + glm::vec4(0, THICK, len, 0));		//position
		_vertices.push_back(glm::vec4(1, 0, 0, 0));
		//5
		_vertices.push_back(pos + glm::vec4(THICK, THICK, 0, 0));	//position
		_vertices.push_back(glm::vec4(0, 0.5, 0, 0));
		//6
		_vertices.push_back(pos + glm::vec4(THICK, THICK, len, 0));	//position
		_vertices.push_back(glm::vec4(1, 0.5, 0, 0));
		//7
		_vertices.push_back(pos + glm::vec4(THICK, 0, 0, 0));		//position
		_vertices.push_back(glm::vec4(0, 0, 0, 0));
		//8
		_vertices.push_back(pos + glm::vec4(THICK, 0, len, 0));		//position
		_vertices.push_back(glm::vec4(1, 0, 0, 0));
	}

	defineBuffers();
}
