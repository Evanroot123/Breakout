#include "shader.h"

#include <iostream>

Shader& Shader::use()
{
	glUseProgram(id);
	return *this;
}

void Shader::compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
	unsigned int sVertex, sFragment, gShader;

	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");

	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");

	if (geometrySource != nullptr)
	{
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}

	id = glCreateProgram();
	glAttachShader(id, sVertex);
	glAttachShader(id, sFragment);
	if (geometrySource != nullptr)
		glAttachShader(id, gShader);
	glLinkProgram(id);
	checkCompileErrors(id, "PROGRAM");
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr)
		glDeleteShader(gShader);
}

void Shader::setFloat(const char* name, float value, bool useShader)
{
	if (useShader)
		use();
	glUniform1f(glGetUniformLocation(id, name), value);
}

void Shader::setInteger(const char* name, int value, bool useShader)
{
	if (useShader)
		use();
	glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::setVector2f(const char* name, float x, float y, bool useShader)
{
	if (useShader)
		use();
	glUniform2f(glGetUniformLocation(id, name), x, y);
}

void Shader::setVector2f(const char* name, const glm::vec2& value, bool useShader)
{
	if (useShader)
		use();
	glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}

void Shader::setVector3f(const char* name, float x, float y, float z, bool useShader)
{
	if (useShader)
		use();
	glUniform3f(glGetUniformLocation(id, name), x, y, z);
}

void Shader::setVector3f(const char* name, const glm::vec3& value, bool useShader)
{
	if (useShader)
		use();
	glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const char* name, float x, float y, float z, float w, bool useShader)
{
	if (useShader)
		use();
	glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}

void Shader::setVector4f(const char* name, const glm::vec4& value, bool useShader)
{
	if (useShader)
		use();
	glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4f(const char* name, const glm::mat4& matrix, bool useShader)
{
	if (useShader)
		use();
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, false, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: type: " << type << "\n" << infoLog << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Link-time error: type: " << type << "\n" << infoLog << "\n" << std::endl;
		}
	}
}