#ifndef SHADER_H
#define SHADER_H

#include <GL\glew.h>
#include <string>
#include <glm\glm.hpp>

class Shader
{
public:
	Shader() { }

	void CompileFromFile(const GLchar* vertexPath,
		const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);

	void CompileFromText(const GLchar* vertexSource,
		const GLchar* fragmentSource, const GLchar* geometrySource = nullptr);

	void Use();

	void SetFloat(const GLchar *name, GLfloat value);
	void SetInteger(const GLchar *name, GLint value);
	void SetVector2f(const GLchar *name, GLfloat x, GLfloat y);
	void SetVector2f(const GLchar *name, const glm::vec2 &vector);
	void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
	void SetVector3f(const GLchar *name, const glm::vec3 &vector);
	void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void SetVector4f(const GLchar *name, const glm::vec4 &vector);
	void SetMatrix4(const GLchar *name, const glm::mat4 &matrix);

	GLuint GetProgram() const;
private:
	GLuint program;

	void CheckShaderErrors(GLuint shader, std::string type);

	void CheckProgramErrors(GLuint program);
};

#endif