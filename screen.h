#ifndef SCREEN_H
#define SCREEN_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "input_handler.h"

class Game;

class Screen
{
public:
	Screen(GLint width, GLint height, Game *game);
	virtual ~Screen() { }
	GLint GetWidth() const;
	GLint GetHeight() const;
	glm::vec2 GetMousePos() const;
	virtual void Update(GLfloat delta) = 0;
	virtual void Render() = 0;

protected:
	Game *game;
	GLint width;
	GLint height;
};

#endif