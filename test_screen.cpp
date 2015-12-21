#include "test_screen.h"
#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include <GL\glew.h>

TestScreen::TestScreen(GLint width, GLint height, Game *game) :
	Screen(width, height, game),
	shader(),
	renderer(&shader),
	memory(new MemBlock(0x10000)),
	cartridge(new Cartridge("res/test_roms/06.gb"))
{
	shader.CompileFromFile("res/shaders/sprite.vs", "res/shaders/sprite.fs");
	processor = new CPU(memory);
	processor->InsertCartridge(cartridge);
}

TestScreen::~TestScreen()
{

}

void TestScreen::Update(GLfloat delta)
{
	processor->Update();
}

void TestScreen::Render()
{
	glClearColor(0.2f, 0.4f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*glLoadIdentity();
	glRasterPos2i(-1, 1);
	glPixelZoom(1, -1);*/


	glm::mat4 projection = glm::ortho(0.0f, (float) width, (float) height, 0.0f);
	shader.SetMatrix4("projection", projection);
	
	MakeScreenTexture();

	renderer.Draw(screenTexture, glm::vec2(0, 0), width, height);

	glDrawPixels(160, 144, GL_RGB, GL_UNSIGNED_BYTE, processor->screenData);
}

void TestScreen::MakeScreenTexture()
{
	screenTexture.SetFormat(GL_RGB, GL_RGB);

	screenTexture.Generate(160, 144, processor->screenData);
	screenTexture.SetFilter(GL_NEAREST, GL_NEAREST);
}