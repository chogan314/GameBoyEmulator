#include "display.h"
#include <iostream>

Display::Display(GLuint width, GLuint height)
: state(UNITIALIZED), width(width), height(height)
{}

GLint Display::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, "2D Engine", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		state = ERROR;
		return -1;
	}

	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError();

	glViewport(0, 0, width, height);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	state = READY;
	return 0;
}

GLboolean Display::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Display::PollEvents()
{
	glfwPollEvents();
}

void Display::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void Display::Terminate()
{
	state = TERMINATED;
	glfwTerminate();
}

void Display::RegisterGamePointer(Game *game)
{
	glfwSetWindowUserPointer(window, game);
}

Display::DisplayState Display::GetState() const
{
	return state;
}

GLFWwindow *Display::GetWindow() const
{
	return window;
}