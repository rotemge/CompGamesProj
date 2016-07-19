#include "Wall.h"
#include "globals.h"
#include <glm\gtc\matrix_transform.hpp>
#include <math.h>

#define THICK 1

Wall::Wall(glm::vec3 center, int size, Direction dir, int pos, int start, int end) :
	//position is the top left corner
	FlatObject(dir == VERTICAL ?
		center - glm::vec3(size / 2 - pos*THICK, 0, size / 2 - start*THICK) :
		center - glm::vec3(size / 2 - start*THICK, 0, size / 2 - pos*THICK),
		"textures\\marble.bmp"),
	_size(size), _start(start), _end(end), _pos(pos), _dir(dir)
{
}

void Wall::init()
{
	Object::init();

	int len = (_end - _start) * THICK;
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
