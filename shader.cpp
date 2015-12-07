#include "shader.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <glm\gtc\type_ptr.hpp>

void Shader::CompileFromFile(const GLchar* vertexPath,
	const GLchar* fragmentPath, const GLchar* geometryPath)
{
	std::string vertexSource;
	std::string fragmentSource;
	std::string geometrySource;

	try
	{
		std::ifstream vertexShaderFile(vertexPath);
		std::ifstream fragmentShaderFile(fragmentPath);
		std::stringstream vertexStream;
		std::stringstream fragmentStream;

		vertexStream << vertexShaderFile.rdbuf();
		fragmentStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexSource = vertexStream.str();
		fragmentSource = fragmentStream.str();

		if (geometryPath != nullptr)
		{
			std::ifstream geometryShaderFile(geometryPath);
			std::stringstream geometryStream;
			geometryStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometrySource = geometryStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cerr << "ERROR: Shader - Failed to read shader files" << std::endl;
	}

	const GLchar *vertexSourceCStr = vertexSource.c_str();
	const GLchar *fragmentSourceCStr = fragmentSource.c_str();
	const GLchar *geometrySourceCStr = geometryPath != nullptr ? geometrySource.c_str() : nullptr;

	CompileFromText(vertexSourceCStr, fragmentSourceCStr, geometrySourceCStr);
}

void Shader::CompileFromText(const GLchar* vertexSource,
	const GLchar* fragmentSource, const GLchar* geometrySource)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint geometryShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	CheckShaderErrors(vertexShader, "Vertex");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	CheckShaderErrors(fragmentShader, "Fragment");

	if (geometrySource != nullptr)
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometrySource, nullptr);
		glCompileShader(geometryShader);
		CheckShaderErrors(geometryShader, "Geometry");
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	if (geometrySource != nullptr)
	{
		glAttachShader(program, geometryShader);
	}
	glLinkProgram(program);
	CheckProgramErrors(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometrySource != nullptr)
	{
		glDeleteShader(geometryShader);
	}
}

void Shader::Use()
{
	glUseProgram(program);
}

void Shader::SetFloat(const GLchar *name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(program, name), value);
}

void Shader::SetInteger(const GLchar *name, GLint value)
{
	glUniform1i(glGetUniformLocation(program, name), value);
}

void Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y)
{
	glUniform2f(glGetUniformLocation(program, name), x, y);
}

void Shader::SetVector2f(const GLchar *name, const glm::vec2 &vector)
{
	glUniform2f(glGetUniformLocation(program, name), vector.x, vector.y);
}

void Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(program, name), x, y, z);
}

void Shader::SetVector3f(const GLchar *name, const glm::vec3 &vector)
{
	glUniform3f(glGetUniformLocation(program, name), vector.x, vector.y, vector.z);
}

void Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(glGetUniformLocation(program, name), x, y, z, w);
}

void Shader::SetVector4f(const GLchar *name, const glm::vec4 &vector)
{
	glUniform4f(glGetUniformLocation(program, name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint Shader::GetProgram() const
{
	return program;
}

void Shader::CheckShaderErrors(GLuint shader, std::string shaderType)
{
	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
		std::cerr << "ERROR: " << shaderType << " shader compile-time error:\n" << infoLog << std::endl;
	}
}

void Shader::CheckProgramErrors(GLuint program)
{
	GLint success;
	GLchar infoLog[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 1024, nullptr, infoLog);
		std::cerr << "ERROR: Shader link-time error:\n" << infoLog << std::endl;
	}
}