#include "display.h"
#include "game.h"
#include "screen.h"
#include "test_screen.h"
#include <iostream>

int main()
{
	const GLuint SCREEN_WIDTH = 800;
	const GLuint SCREEN_HEIGHT = 600;

	const GLfloat updateRate = 1.0f / 120.0f;

	Display display(SCREEN_WIDTH, SCREEN_HEIGHT);
	display.Init();
	if (display.GetState() == Display::ERROR)
	{
		return -1;
	}

	Game game(&display);
	TestScreen *screen = new TestScreen(SCREEN_WIDTH, SCREEN_HEIGHT, &game);
	game.SetScreen(screen);

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = glfwGetTime();
	GLfloat accumulatedTime = 0.0f;
	GLfloat frameTime = 0.0f;
	GLint frames = 0;

	while (!display.ShouldClose())
	{
		display.PollEvents();

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		accumulatedTime += deltaTime;
		frameTime += deltaTime;
		frames++;

		while (accumulatedTime >= updateRate)
		{
			accumulatedTime -= updateRate;
			game.Update(updateRate);
		}

		while (frameTime > 1.0f)
		{
			std::cout << "FPS: " << frames << std::endl;
			frames = 0;
			frameTime -= 1.0f;
		}

		game.Render();

		display.SwapBuffers();
	}

	display.Terminate();

	return 0;
}