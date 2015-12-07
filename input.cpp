#include "input.h"
#include "game.h"
#include "input_handler.h"
#include "screen.h"

Input::Input(GLFWwindow* window) : handler(nullptr)
{
	for (int i = 0; i < 1024; i++)
	{
		keys[i] = false;
		mouseButtons[i] = false;
	}
	glfwSetKeyCallback(window, OnKey);
	glfwSetCursorPosCallback(window, OnMouseMove);
	glfwSetMouseButtonCallback(window, OnMouseButton);
	glfwSetScrollCallback(window, OnMouseScroll);
}

void Input::RegisterHandler(InputHandler* handler)
{
	this->handler = handler;
}

void Input::RemoveHandler()
{
	this->handler = nullptr;
}

bool Input::KeyPressed(int key)
{
	return keys[key];
}

bool Input::MouseButtonPressed(int button)
{
	return mouseButtons[button];
}

float Input::GetMouseX()
{
	return mouseX;
}

float Input::GetMouseY()
{
	return mouseY;
}

void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	Input* input = game->GetInput();
	InputHandler* handler = input->handler;

	if (action == GLFW_PRESS)
	{
		input->keys[key] = true;
		if (handler)
		{
			handler->OnKeyDown(key, mods);
		}
	}
	else if (action == GLFW_RELEASE)
	{
		input->keys[key] = false;
		if (handler)
		{
			handler->OnKeyUp(key, mods);
		}
	}
}

void OnMouseMove(GLFWwindow* window, double x, double y)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	Input* input = game->GetInput();
	InputHandler* handler = input->handler;

	input->mouseX = (float) x;
	input->mouseY = (float) y;
	if (handler)
	{
		handler->OnMouseMoved((float) x, (float) y);
	}
}

void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	Input* input = game->GetInput();
	InputHandler* handler = input->handler;

	if (action == GLFW_PRESS)
	{
		input->mouseButtons[button] = true;
		if (handler)
		{
			handler->OnMouseDown(button, mods);
		}
	}
	else if (action == GLFW_RELEASE)
	{
		input->mouseButtons[button] = false;
		if (handler)
		{
			handler->OnMouseUp(button, mods);
		}
	}
}

void OnMouseScroll(GLFWwindow* window, double xOffset, double yOffset)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	Input* input = game->GetInput();
	InputHandler* handler = input->handler;

	if (handler)
	{
		handler->OnMouseScroll((float) xOffset, (float) yOffset);
	}
}