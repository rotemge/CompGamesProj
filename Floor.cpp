#include "Floor.h"


Floor::Floor(glm::vec3 center, float size) :
	FlatObject(center, "textures\\teapot.bmp"), _width(size), _height(size)
{ }

void Floor::init()
{
	Object::init();

	// Create vertices
	glm::vec4 pos(_position, 1);
	//lower left corner
	_vertices.push_back(pos + glm::vec4(-_width / 2, 0, -_height / 2, 0));	//position
	_vertices.push_back(glm::vec4(0, 1, 0, 0));								//texture coordinates
	//upper left corner
	_vertices.push_back(pos + glm::vec4(-_width / 2, 0, _height / 2, 0));	//position
	_vertices.push_back(glm::vec4(0, 0, 0, 0));								//texture coordinates
	//lower right corner
	_vertices.push_back(pos + glm::vec4(_width / 2, 0, -_height / 2, 0));	//position
	_vertices.push_back(glm::vec4(1, 1, 0, 0));								//texture coordinates
	//upper right corner
	_vertices.push_back(pos + glm::vec4(_width / 2, 0, _height / 2, 0));	//position
	_vertices.push_back(glm::vec4(1, 0, 0, 0));								//texture coordinates

	defineBuffers();
}

