#include "Game.h"
#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#ifdef POST_PROCESSING
#include "PPBuffer.h"
#endif
#ifdef INPUT_MANAGER
#include "InputManager.h"
#endif

enum KeyControls
{
	KEY_ESC = (27),
	KEY_PAUSE = (' '),

	// game controls
	KEY_UP = ('w'),
	KEY_DOWN = ('s'),
	KEY_LEFT = ('a'),
	KEY_RIGHT = ('d')
};

int const WINDOW_WIDTH = 512;
int const WINDOW_HEIGHT = 512;

Game* _world;
#ifdef POST_PROCESSING
PPBuffer* _ppbuffer;
#endif
#ifdef INPUT_MANAGER
InputManager* _inputManager;
#endif

void init();
void display();
void keyboard(unsigned char key, int x, int y);
void update();
void resizeWindowHandler(int width, int height);
//void timer(int value);

int main(int argc, char **argv)
{
	srand(static_cast <unsigned> (time(0)));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow(argv[0]);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr << "Error initializing glew: " << glewGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	//glutKeyboardUpFunc
	glutIdleFunc(update);
	glutReshapeFunc(resizeWindowHandler);

	glutMainLoop();

	if (NULL != _world) { delete _world; }
#ifdef POST_PROCESSING
	if (NULL != _ppbuffer) { delete _ppbuffer; }
#endif

	return 0;
}

void init(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glFrontFace(GL_CW);
	glDisable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Creating the world
	_world = new Game();
	_world->init();

#ifdef POST_PROCESSING
	// Creating post-processing buffer
	_ppbuffer = new PPBuffer();
	_ppbuffer->init(WINDOW_WIDTH, WINDOW_HEIGHT);

	_world->setPPBuffer(_ppbuffer);
#endif
#ifdef INPUT_MANAGER
	// Creating input manager
	_inputManager = new InputManager(_world);
#endif
}

void display(void)
{
#ifdef POST_PROCESSING
	_ppbuffer->setup();
#endif

	//glClearColor(1.0, 0.4, 0.0, 0.0); //background color (default is black)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the window

	_world->draw();
#ifdef POST_PROCESSING
	_ppbuffer->render();
#endif

	// Swap those buffers so someone will actually see the results... //
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	unsigned int lowerKey = tolower(key);

	switch (tolower(lowerKey))
	{
	case KEY_UP:
		_world->upKeyPressed();
		break;
	case KEY_DOWN:
		_world->downKeyPressed();
		break;
	case KEY_RIGHT:
		_world->rightKeyPressed();
		break;
	case KEY_LEFT:
		_world->leftKeyPressed();
		break;
	case KEY_PAUSE:
		_world->pauseGame();
		break;
	case KEY_ESC:
		exit(0);
		break;

	default:
#ifdef INPUT_MANAGER
		_inputManager.longTermKeyDown(lowerKey, x, y);
#endif
		break;
	}
}

void update()
{
	static int currentTime, deltaTime, prevTime = 0;
	static int startTime, elapsedTime = 0;
	currentTime = glutGet(GLUT_ELAPSED_TIME); // milliseconds
	deltaTime = currentTime - prevTime;
	prevTime = currentTime;

	_world->update(deltaTime);

	glutPostRedisplay();
}

void resizeWindowHandler(int width, int height)
{
#ifdef POST_PROCESSING
	_ppbuffer->resize(width, height);
#endif
	//_world->resize(width, height);

	// set the new viewport
	glViewport(0, 0, width, height);
}

void timer(int value)
{
	glutTimerFunc(25, timer, ++value);   // uint millis int value

	_world->update(value);

#ifdef INPUT_MANAGER
	_inputManager->timeEvents(); // Input timed events (e.g. smooth moving)
#endif

	glutPostRedisplay();
}