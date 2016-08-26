#include "Game.h"
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>

#define CENTER glm::vec3(0, 0, 0)
#define halfThick ((float)SIZE_ / GRID / 2)
#define halfSize (SIZE_ / 2)
#define thickness ((float)SIZE_ / GRID)

Game::Game() : _lightPos(0, 5, 0), _camPos(0, 20, 20), _floor(CENTER, SIZE_), 
				_player(glm::vec3(halfThick, thickness, halfSize + halfThick), halfSize - halfThick), _isKeyReleased(false)
{
}

void Game::init() {
	_view = glm::lookAt(_camPos, CENTER, glm::vec3(0, 1, 0));
	_projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	
	_walls.push_back(new Wall(CENTER, SIZE_, Wall::HORIZONTAL, 0, 0, GRID, thickness, false));
	_walls.push_back(new Wall(CENTER, SIZE_, Wall::HORIZONTAL, GRID - 1, 0, GRID, thickness, false));
	_walls.push_back(new Wall(CENTER, SIZE_, Wall::VERTICAL,   0, 1, GRID - 1, thickness, false));
	_walls.push_back(new Wall(CENTER, SIZE_, Wall::VERTICAL,   GRID - 1, 1, GRID - 1, thickness, false));

	_enemies[0] = new EnemyBall((GRID / 2 - 1) * thickness);
	
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

int posToIndex(float pos) {
	return (floor(pos / thickness) * thickness + halfSize) / thickness;
}

void Game::update(float deltaTime)
{
	// player
	glm::vec3 nextPos = _player.getNextPosition(deltaTime);
	glm::vec3 curPos = _player.getPosition();
	bool isHit = handleBallMovement(deltaTime, nextPos);
	if (!isHit) {
		_player.update(deltaTime);
		if (_player.isMoving()) {
			// create\update temp wall
			if (_walls.back()->isTemp() 
				&& ((nextPos.z == curPos.z && _walls.back()->getDirection() == Wall::HORIZONTAL) 
					|| (nextPos.x == curPos.x && _walls.back()->getDirection() == Wall::VERTICAL))) {
				// use existing wall
				Wall* w = _walls.back();
				_walls.pop_back();
				int lim;
				if (nextPos.z == curPos.z) { //HORIZONTAL 
					lim = posToIndex(nextPos.x);
					if (nextPos.x < curPos.x) {
						lim++;
					}
				}
				else {
					lim = posToIndex(nextPos.z);
					if (nextPos.z < curPos.z) {
						lim++;
					}
				}
				_walls.push_back(new Wall(CENTER, SIZE_, w->getDirection(), w->getIndex(), 
					std::min({ w->getStart(), w->getEnd(), lim }), std::max({ w->getStart(), w->getEnd(), lim }), thickness, true));
				_walls.back()->init();
				delete w;
			}
			else {
				// create new wall
				if (nextPos.z == curPos.z) {
					int index = posToIndex(curPos.z);
					int start = posToIndex(curPos.x);
					int end = posToIndex(nextPos.x);
					if (nextPos.x < curPos.x) {
						start++;
						end++;
					}
					_walls.push_back(new Wall(CENTER, SIZE_, Wall::HORIZONTAL, index, std::min(start, end), std::max(start, end), thickness, true));
				}
				else {
					int index = posToIndex(curPos.x);
					int start = posToIndex(curPos.z);
					int end = posToIndex(nextPos.z);
					if (nextPos.z < curPos.z) {
						start++;
						end++;
					}
					_walls.push_back(new Wall(CENTER, SIZE_, Wall::VERTICAL, index, std::min(start, end), std::max(start, end), thickness, true));
				}
				_walls.back()->init();
			}
		}		
	}

	// enemies
	for (EnemyBall *b : _enemies) {
		b->update(deltaTime);
		for (Wall* w : _walls) {
			if (w->hitWithBall(b->getPosition(), b->getRadius())) {
				if (w->isTemp()) {
					lifeLost();
				}
				else {
					b->hit(w->getDirection());
				}
				break;
			}
		}
	}
}

/** returns true if the ball stopped for some reason */
bool Game::handleBallMovement(float deltaTime, glm::vec3 nextPos) {
	for (Wall* w : _walls) {
		bool curOverlap = w->gridOverlap(posToIndex(_player.getPosition().z), posToIndex(_player.getPosition().x));
		bool nextOverlap = w->gridOverlap(posToIndex(nextPos.z), posToIndex(nextPos.x));
		if (_isKeyReleased && !w->isTemp() && curOverlap) {
			// key released on wall
			_player.move(Player::MOVE_NONE);
			_isKeyReleased = false;
			return true;
		}
		if (nextOverlap && w->isTemp()) {
			// hit a temporary wall
			lifeLost();
			_player.update(deltaTime);
			return true;
		}
		if (!curOverlap && nextOverlap && !w->isTemp()) {
			// got to a wall
			_player.update(deltaTime);
			_player.move(Player::MOVE_NONE);
			while (_walls.back()->isTemp()) {
				_walls.back()->setTemp(false);
			}
			std::cout << "got to a wall" << std::endl;
			return true;
		}
	}
	return false;
}

void Game::lifeLost() {
	std::cout << "DIE" << std::endl;
	// TODO:
	// player back to start position
	// destroy temp wall(s)
	//while (_walls.back()->isTemp()) {
	//	delete _walls.back();
	//	_walls.pop_back();
	//}
	// update lives - actual and on screen
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
