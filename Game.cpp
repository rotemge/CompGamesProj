#include "Game.h"
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>

#define CENTER glm::vec3(0, 0, 0)

Game::Game() : _lightPos(0, 5, 0), _camPos(0, 20, 20), _floor(CENTER, SIZE_), 
				_player(glm::vec3(0, (float)SIZE_ / GRID, SIZE_ / 2 + 0.5), SIZE_ / 2 - (float)SIZE_ / GRID / 2), _isKeyReleased(false)
{
}

void Game::init() {
	_view = glm::lookAt(_camPos, CENTER, glm::vec3(0, 1, 0));
	_projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	
	float thick = (float) SIZE_ / GRID;
	_walls.push_back(new Wall(CENTER, SIZE_, Wall::HORIZONTAL, 0, 0, GRID, thick, false));
	_walls.push_back(new Wall(CENTER, SIZE_, Wall::HORIZONTAL, GRID - 1, 0, GRID, thick, false));
	_walls.push_back(new Wall(CENTER, SIZE_, Wall::VERTICAL,   0, 1, GRID - 1, thick, false));
	_walls.push_back(new Wall(CENTER, SIZE_, Wall::VERTICAL,   GRID - 1, 1, GRID - 1, thick, false));

	_enemies[0] = new EnemyBall((GRID / 2 - 1) * thick);
	
	for (Wall* w : _walls) {
		w->init();
	}
	for (EnemyBall *b : _enemies) {
		b->init();
	}
	_floor.init();
	_player.init();
}

void Game::draw()
{
	glm::vec4 lightColor(0.8, 0.8, 0.7, 1);
	_floor.draw(_projection, _view, _camPos, _lightPos, lightColor);
	_player.draw(_projection, _view, _camPos, _lightPos, lightColor);
	for (Wall* w:_walls){
		w->draw(_projection, _view, _camPos, _lightPos, lightColor);
	}
	for (EnemyBall *b : _enemies) {
		b->draw(_projection, _view, _camPos, _lightPos, lightColor);
	}
}

void Game::update(float deltaTime)
{
	// player
	bool isHit = handleBallMovement(deltaTime);
	if (!isHit) _player.update(deltaTime);

	// enemies
	for (EnemyBall *b : _enemies) {
		b->update(deltaTime);
		for (Wall* w : _walls) {
			if (w->hitWithBall(b->getPosition(), b->getRadius())) {
				b->hit(w->getDirection());
				break;
			}
		}
	}
}

bool Game::handleBallMovement(float deltaTime) {
	glm::vec3 nextPos = _player.getNextPosition(deltaTime);
	for (Wall* w : _walls) {
		if (_isKeyReleased && w->hitWithBall(_player.getPosition(), 0) && !w->isTemp()) {
			_player.move(Player::MOVE_NONE);
			_isKeyReleased = false;
			return true;
		}
		if (w->hitWithBall(_player.getPosition(), 0) && w->isTemp()) {
			// die!!
			_player.update(deltaTime);
			return true;
		}
		if (!w->hitWithBall(_player.getPosition(), 0)
			&& w->hitWithBall(nextPos, 0) && !w->isTemp()) {
			_player.update(deltaTime);
			_player.move(Player::MOVE_NONE);
			std::cout << "got to a wall" << std::endl;
			return true;
		}
	}
	return false;
}

void Game::moveKeyReleased() {
	_isKeyReleased = true;
}

void Game::upKeyPressed() {
	_player.move(Player::MOVE_UP);
}

void Game::downKeyPressed() {
	_player.move(Player::MOVE_DOWN);
}

void Game::rightKeyPressed() {
	_player.move(Player::MOVE_RIGHT);
}

void Game::leftKeyPressed() {
	_player.move(Player::MOVE_LEFT);
}

void Game::pauseGame() {
}

Game::~Game()
{
	for (Wall* w : _walls) {
		delete w;
	}
	for (EnemyBall* b : _enemies) {
		delete b;
	}
}
