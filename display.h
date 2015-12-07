#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Game;

class Display
{
public:
	enum DisplayState
	{
		UNITIALIZED,
		READY,
		ERROR,
		TERMINATED
	};

	Display(GLuint width, GLuint height);
	GLint Init();
	GLboolean ShouldClose();
	void PollEvents();
	void SwapBuffers();
	void Terminate();
	void RegisterGamePointer(Game *game);

	DisplayState GetState() const;
	GLFWwindow *GetWindow() const;
private:
	DisplayState state;
	GLuint width;
	GLuint height;
	GLFWwindow *window;
};

#endif