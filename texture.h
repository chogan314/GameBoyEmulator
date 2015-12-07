#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <GL\glew.h>

class Texture
{
public:
	Texture();
	void LoadFromFile(const GLchar *file);
	void Generate(GLuint width, GLuint height, void* data);
	void SetFilter(GLuint minFilter, GLuint magFilter);
	void SetWrap(GLuint uWrap, GLuint vWrap);
	void SetFormat(GLuint internalFormat, GLuint imageFormat);
	void Bind() const;
	void Unbind() const;
	GLint GetWidth() const;
	GLint GetHeight() const;
private:
	GLuint id;
	GLuint width;
	GLuint height;
	GLuint internalFormat;
	GLuint imageFormat;
	GLuint minFilter;
	GLuint magFilter;
	GLuint uWrap;
	GLuint vWrap;
};

#endif