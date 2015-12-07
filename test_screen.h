#ifndef TEST_SCREEN_H
#define TEST_SCREEN_H

#include "screen.h"
#include "cpu.h"
#include "shader.h"
#include "sprite_renderer.h"

class TestScreen : public Screen
{
public:
	TestScreen(GLint width, GLint height, Game *game);
	~TestScreen();

	void Update(GLfloat delta);
	void Render();

private:
	Shader shader;
	SpriteRenderer renderer;
	CPU *processor;
	MemBlock *memory;
	Cartridge *cartridge;
	Texture screenTexture;

	void MakeScreenTexture();
};

#endif