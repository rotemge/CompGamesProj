#pragma once

#include <vector>
#include "Floor.h"
#include "Wall.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	void init();
	void draw();
	void update(int deltaTime);  // milliseconds

	void upKeyPressed();
	void downKeyPressed();
	void rightKeyPressed();
	void leftKeyPressed();
	void pauseGame();

private:
	glm::mat4 _view;
	glm::mat4 _projection;
	glm::vec3 _lightPos;
	glm::vec3 _camPos;

	//game objects
	Floor _floor;
	std::vector<Wall*> _walls;
	Player _player;

	//void _updateLivesText(const char* text);
};

