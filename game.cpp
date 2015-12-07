#include "game.h"
#include "screen.h"

Game::Game(Display *display) : screen(nullptr), display(display)
{
	display->RegisterGamePointer(this);
	input = new Input(display->GetWindow());
}

Game::~Game()
{
	delete input;
	delete screen;
}

void Game::Update(float delta)
{
	if (screen)
	{
		screen->Update(delta);
	}
}

void Game::Render()
{
	if (screen)
	{
		screen->Render();
	}
}

void Game::SetScreen(Screen *screen)
{
	delete this->screen;
	this->screen = screen;
}

Input *Game::GetInput()
{
	return input;
}