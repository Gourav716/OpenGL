#include"Headers/Shader.h"
#include<glad/glad.h>
#include<fstream>
#include<glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
{
	ShaderID = glad_glCreateProgram();

	std::string vertexSource = GetFileContents(vertexFile);
	std::string fragmentSource = GetFileContents(fragmentFile);

	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource.c_str());
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

	glad_glAttachShader(ShaderID, vertexShader);
	glad_glAttachShader(ShaderID, fragmentShader);

	glad_glLinkProgram(ShaderID);
	glad_glValidateProgram(ShaderID);

	glad_glDeleteShader(ShaderID);
}

Shader::~Shader()
{
	glDeleteProgram(ShaderID);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glad_glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	glad_glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4 matrix)
{
	glad_glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value_ptr(matrix));
}

void Shader::Activate()
{
	glUseProgram(ShaderID);
}

void Shader::Deactivate()
{
	glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name)
{
	return glad_glGetUniformLocation(ShaderID, name.c_str());
}

unsigned int Shader::CompileShader(unsigned int type, const char* src)
{
	unsigned int shader = glad_glCreateShader(type);
	glad_glShaderSource(shader, 1, &src, NULL);
	glad_glCompileShader(shader);

	return shader;
}

std::string Shader::GetFileContents(const std::string& file)
{
	std::string contents;
	std::ifstream stream(file);
	contents.assign(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());

	return contents;;
}
