#include "Walls.h"
#include "globals.h"
#include <glm\gtc\matrix_transform.hpp>
#include <math.h>

#define THICK 0.5

Walls::Walls(glm::vec3 center, float size, float rot) :
	FlatObject(center, "textures\\marble.bmp"), _size(size)
{ 
	float rads = (float)(rot / 180 * M_PI);
	_model = glm::rotate(glm::mat4(1.f), rads, glm::vec3(0.f, 1.f, 0.f));
}

void Walls::init()
{
	Object::init();
	float halfSize = _size / 2;

	glm::vec4 pos(_position, 1);
	//1
	_vertices.push_back(pos + glm::vec4(-halfSize, 0, halfSize, 0));	//position
	_vertices.push_back(glm::vec4(0, 0.5, 0, 0));
	//2
	_vertices.push_back(pos + glm::vec4(halfSize, 0, halfSize, 0));	//position
	_vertices.push_back(glm::vec4(1, 0.5, 0, 0));
	//3
	_vertices.push_back(pos + glm::vec4(-halfSize, THICK, halfSize, 0));	//position
	_vertices.push_back(glm::vec4(0, 0, 0, 0));
	//4
	_vertices.push_back(pos + glm::vec4(halfSize, THICK, halfSize, 0));	//position
	_vertices.push_back(glm::vec4(1, 0, 0, 0));
	//5
	_vertices.push_back(pos + glm::vec4(-halfSize/*+THICK*/, THICK, halfSize-THICK, 0));	//position
	_vertices.push_back(glm::vec4(0, 0.5, 0, 0));
	//6
	_vertices.push_back(pos + glm::vec4(halfSize/*-THICK*/ , THICK, halfSize-THICK, 0));	//position
	_vertices.push_back(glm::vec4(1, 0.5, 0, 0));
	//7
	_vertices.push_back(pos + glm::vec4(-halfSize/* + THICK*/ , 0, halfSize - THICK, 0));	//position
	_vertices.push_back(glm::vec4(0, 0, 0, 0));
	//8
	_vertices.push_back(pos + glm::vec4(halfSize/* - THICK*/ , 0, halfSize - THICK, 0));	//position
	_vertices.push_back(glm::vec4(1, 0, 0, 0));

	defineBuffers();
}
