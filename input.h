#ifndef INPUT_H
#define INPUT_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class InputHandler;

class Input
{
public:
	Input(GLFWwindow *window);
	void RegisterHandler(InputHandler *handler);
	void RemoveHandler();
	bool KeyPressed(int key);
	bool MouseButtonPressed(int button);
	float GetMouseX();
	float GetMouseY();
private:
	InputHandler *handler;
	bool keys[1024];
	float mouseX, mouseY;
	bool mouseButtons[1024];

	friend void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void OnMouseMove(GLFWwindow* window, double x, double y);
	friend void OnMouseButton(GLFWwindow* window, int button, int action, int mods);
	friend void OnMouseScroll(GLFWwindow* window, double xOffset, double yOffset);
};

#endif