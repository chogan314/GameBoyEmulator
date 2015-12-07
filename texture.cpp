#include "texture.h"
#include <SOIL\SOIL.h>

Texture::Texture() : width(0), height(0), internalFormat(GL_RGBA),
imageFormat(GL_RGBA), minFilter(GL_LINEAR), magFilter(GL_LINEAR),
uWrap(GL_REPEAT), vWrap(GL_REPEAT)
{
	glGenTextures(1, &id);
}

void Texture::LoadFromFile(const GLchar *file)
{
	int w, h;
	unsigned char* image = SOIL_load_image(file, &w, &h, 0, SOIL_LOAD_RGBA);
	Generate(w, h, image);
	SOIL_free_image_data(image);
}

void Texture::Generate(GLuint width, GLuint height, void* data)
{
	this->width = width;
	this->height = height;
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
		width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, uWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, vWrap);
	Unbind();
}

void Texture::SetFilter(GLuint minFilter, GLuint magFilter)
{
	this->minFilter = minFilter;
	this->magFilter = magFilter;
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	Unbind();
}

void Texture::SetWrap(GLuint uWrap, GLuint vWrap)
{
	this->uWrap = uWrap;
	this->vWrap = vWrap;
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, uWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, vWrap);
	Unbind();
}

void Texture::SetFormat(GLuint internalFormat, GLuint imageFormat)
{
	this->internalFormat = internalFormat;
	this->imageFormat = imageFormat;
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLint Texture::GetWidth() const
{
	return width;
}

GLint Texture::GetHeight() const
{
	return height;
}