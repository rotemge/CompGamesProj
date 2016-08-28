#include "Game.h"
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
#include <GL\glut.h> //glutBitmapCharacter

#define MAX_LIVES 5
#define CENTER glm::vec3(0, 0, 0)
#define halfThick ((float)SIZE_ / GRID / 2)
#define halfSize (SIZE_ / 2)
#define thickness ((float)SIZE_ / GRID)

void print_bitmap_string(void* font, char* s) {
	if (s && strlen(s)) {
		while (*s) {
			glutBitmapCharacter(font, *s);
			s++;
		}
	}
}

void updateLivesText(int lives) {
	std::string lifeText = std::string("LIVES: ") + std::to_string(lives);
	char t[10] = { '\0' };
	strcpy_s(t, strlen(lifeText.c_str()) + 1, lifeText.c_str());

	glRasterPos2f(-0.95f, 0.92f);
	print_bitmap_string(GLUT_BITMAP_8_BY_13, t);
}

void setDeadText() {
	char t[30] = { '\0' };

	char* lifeText = "YOU LOST";
	size_t len = strlen(lifeText);
	strcpy_s(t, len + 1, lifeText);
	float pos = -(18.f * (len / 2)) / glutGet(GLUT_WINDOW_WIDTH);
	glRasterPos2f(pos, 0.1f);
	print_bitmap_string(GLUT_BITMAP_9_BY_15, t);

	lifeText = "press space for a new game";
	len = strlen(lifeText);
	strcpy_s(t, len + 1, lifeText);
	pos = -(15.f * (len / 2)) / glutGet(GLUT_WINDOW_WIDTH);
	glRasterPos2f(pos, -0.1f);
	print_bitmap_string(GLUT_BITMAP_9_BY_15, t);
}

void setPauseText() {
	char t[30] = { '\0' };

	char* text = "PAUSED";
	size_t len = strlen(text);
	strcpy_s(t, len + 1, text);
	float pos = -(18.f * (len / 2)) / glutGet(GLUT_WINDOW_WIDTH);
	glRasterPos2f(pos, 0.1f);
	print_bitmap_string(GLUT_BITMAP_9_BY_15, t);

	text = "press space to continue";
	len = strlen(text);
	strcpy_s(t, len + 1, text);
	pos = -(15.f * (len / 2)) / glutGet(GLUT_WINDOW_WIDTH);
	glRasterPos2f(pos, -0.1f);
	print_bitmap_string(GLUT_BITMAP_9_BY_15, t);
}

int posToIndex(float pos) {
	return (floor(pos / thickness) * thickness + halfSize) / thickness;
}

Game::Game() : _lightPos(0, 5, 0), _camPos(0, 18, 18), _floor(CENTER, SIZE_), 
				_player(glm::vec3(halfThick, thickness, halfSize - thickness), halfSize - halfThick),
				_isKeyReleased(false), _lives(MAX_LIVES), _paused(false)
{
}

void Game::init() {
	_view = glm::lookAt(_camPos, CENTER, glm::vec3(0, 1, 0));
	_projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	
	_walls.push_back(new Wall(CENTER, SIZE_, Wall::HORIZONTAL, 0, 0, GRID, thickness, false));
	_walls.push_back(new Wall(CENTER, SIZE_, Wall::HORIZONTAL, GRID - 1, 0, GRID, thickness, false));
	_walls.push_back(new Wall(CENTER, SIZE_, Wall::VERTICAL,   0, 1, GRID - 1, thickness, false));
	_walls.push_back(new Wall(CENTER, SIZE_, Wall::VERTICAL,   GRID - 1, 1, GRID - 1, thickness, false));

	for (int i = 0; i < ENEMIES; i++) {
		_enemies[i] = new EnemyBall((GRID / 2 - 1) * thickness);
	}
	
	for (Wall* w : _walls) {
		w->init();
	}
	for (EnemyBall *b : _enemies) {
		b->init();
	}
	_floor.init();
	_player.init();
	updateLivesText(_lives);
}

void Game::draw()
{
	if (_lives == 0) {
		setDeadText();
		return;
	}
	if (_paused) setPauseText();
	glm::vec4 lightColor(0.8, 0.8, 0.7, 1);
	_floor.draw(_projection, _view, _camPos, _lightPos, lightColor);
	_player.draw(_projection, _view, _camPos, _lightPos, lightColor);
	for (Wall* w:_walls){
		w->draw(_projection, _view, _camPos, _lightPos, lightColor);
	}
	for (EnemyBall *b : _enemies) {
		b->draw(_projection, _view, _camPos, _lightPos, lightColor);
	}
	updateLivesText(_lives);
}

void Game::update(float deltaTime)
{
	if (_lives == 0 || _paused) return;
	// player
	glm::vec3 nextPos = _player.getNextPosition(deltaTime);
	bool isHit = handlePlayerMovement(deltaTime, nextPos);
	if (!isHit) {
		handleWallBuilding(nextPos);
		_player.update(deltaTime);		
	}

	handleEnemiesMovment(deltaTime);	
}

void Game::handleEnemiesMovment(float deltaTime) {
	for (EnemyBall *b : _enemies) {
		for (Wall* w : _walls) {
			if (w->hitWithBall(b->getPosition(), b->getRadius())) {
				if (w->isTemp()) {
					lifeLost();
					break;
				}
				else {
					b->hit(w->getDirection());
					break;
				}
			}
		}
		for (EnemyBall *b2 : _enemies) {
			if (b2 == b) continue;
			if (glm::distance(b->getPosition(), b2->getPosition()) <= b->getRadius() + b2->getRadius()) {
				b->hit(Wall::VERTICAL);;
				b2->hit(Wall::HORIZONTAL);
			}
		}
		b->update(deltaTime);
	}
}

void Game::handleWallBuilding(glm::vec3 nextPos) {
	if (!_player.isMoving()) return;
	glm::vec3 curPos = _player.getPosition();
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

/** returns true if the ball stopped for some reason */
bool Game::handlePlayerMovement(float deltaTime, glm::vec3 nextPos) {
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
			handleWallBuilding(nextPos);
			_player.update(deltaTime);
			_player.move(Player::MOVE_NONE);
			for (Wall* w : _walls) {
				if (w->isTemp()) w->setTemp(false);
			}
			std::cout << "DEBUG :: got to a wall" << std::endl;
			return true;
		}
		if (curOverlap) {
			_player.update(deltaTime);
			return true;
		}
	}
	return false;
}

void Game::lifeLost() {
	std::cout << "DEBUG :: DIE" << std::endl;
	// player back to start position
	_player.resetPos(glm::vec3(halfThick, thickness, halfSize - thickness));
	// destroy temp wall(s)
	while (_walls.back()->isTemp()) {
		delete _walls.back();
		_walls.pop_back();
	}
	// update lives - actual and on screen
	_lives--;
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
	if (_lives == 0) {
		_lives = MAX_LIVES;
		_isKeyReleased = false;
		_paused = false;
		while (_walls.size() > 4) {
			delete _walls.back();
			_walls.pop_back();
		}
		return;
	}
	_paused = !_paused;
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
