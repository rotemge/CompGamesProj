#pragma once

#include <vector>
#include "Floor.h"
#include "Wall.h"
#include "Player.h"
#include "EnemyBall.h"

#define SIZE_ 20
#define GRID 40
#define ENEMIES 1

class Game
{
public:
	Game();
	~Game();
	void init();
	void draw();
	void update(float deltaTime);  // seconds

	void upKeyPressed();
	void downKeyPressed();
	void rightKeyPressed();
	void leftKeyPressed();
	void moveKeyReleased();
	void pauseGame();

private:
	enum WallState
	{
		NONE,
		TEMP,
		DONE
	};

	glm::mat4 _view;
	glm::mat4 _projection;
	glm::vec3 _lightPos;
	glm::vec3 _camPos;

	//game objects
	Floor _floor;
	std::vector<Wall*> _walls;
	EnemyBall* _enemies[ENEMIES];
	Player _player;
	bool _isKeyReleased;
	int _lives;
	bool _paused;

	bool handlePlayerMovement(float deltaTime, glm::vec3 nextPos);
	void handleWallBuilding(glm::vec3 nextPos);
	void handleEnemiesMovment(float deltaTime);
	void lifeLost();
};

