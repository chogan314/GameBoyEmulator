#ifndef GAME_H
#define GAME_H

#include <GL\glew.h>

#include "display.h"
#include "input.h"

class Screen;

class Game
{
public:
	Game(Display* display);
	~Game();
	void Update(GLfloat delta);
	void Render();
	void SetScreen(Screen *screen);
	Input *GetInput();
private:
	Display *display;
	Input *input;
	Screen *screen;
};

#endif;	