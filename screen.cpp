#include "screen.h"
#include "game.h"

Screen::Screen(GLint width, GLint height, Game *game) :
width(width),
height(height),
game(game)
{
}

GLint Screen::GetHeight() const
{
	return height;
}

GLint Screen::GetWidth() const
{
	return width;
}

glm::vec2 Screen::GetMousePos() const
{
	return glm::vec2(game->GetInput()->GetMouseX(), game->GetInput()->GetMouseY());
}