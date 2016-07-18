#include "Game.h"
#include <glm\gtc\matrix_transform.hpp>

#define CENTER glm::vec3(0, 0, 0)
#define SIZE 20

Game::Game() : _lightPos(0, 17, 0), _camPos(0, 17, 20), _floor(CENTER, SIZE), _player(glm::vec3(0, 2, SIZE / 2))
{
}

void Game::init() {
	_view = glm::lookAt(_camPos, CENTER, glm::vec3(0, 1, 0));
	_projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

	for (int i = 0; i < 4; i++) {
		_walls.push_back(new Walls(CENTER, SIZE, 90 * i));
		_walls.back()->init();
	}
	_floor.init();
	_player.init();
}

void Game::draw()
{
	glm::vec4 lightColor(1, 1, 0.9, 1);
	_floor.draw(_projection, _view, _camPos, _lightPos, lightColor);
	_player.draw(_projection, _view, _camPos, _lightPos, lightColor);
	for (Walls* w:_walls){
		w->draw(_projection, _view, _camPos, _lightPos, lightColor);
	}	
}

void Game::update(int deltaTime)
{
	_floor.update(deltaTime);
	_player.update(deltaTime);
	for (Walls* w : _walls) {
		w->update(deltaTime);
	}
}

void Game::upKeyPressed()
{
	if (_player.getPosition().z - (_player.getSize() / 2) > -SIZE / 2) {
		_player.move(Player::MOVE_UP);
	}	
}

void Game::downKeyPressed()
{
	if (_player.getPosition().z + (_player.getSize() / 2) < SIZE / 2) {
		_player.move(Player::MOVE_DOWN);
	}
}

void Game::rightKeyPressed()
{
	if (_player.getPosition().x + (_player.getSize() / 2) < SIZE / 2) {
		_player.move(Player::MOVE_RIGHT);
	}
}

void Game::leftKeyPressed()
{
	if (_player.getPosition().x - (_player.getSize() / 2) > -SIZE / 2) {
		_player.move(Player::MOVE_LEFT);
	}
}

void Game::pauseGame()
{
}


Game::~Game()
{
	for (Walls* w : _walls) {
		delete w;
	}
}
