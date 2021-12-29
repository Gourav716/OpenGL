#ifndef SHADER_CLASS
#define SHADER_CLASS

#include<string>
#include<glm/glm.hpp>

class Shader
{
public:
	Shader(const std::string& vertexFile, const std::string& fragmentFile);
	~Shader();

	void SetUniform1i(const std::string& name, int value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniformMat4f(const std::string& name, glm::mat4 matrix);

	void Activate();
	void Deactivate();

private:
	unsigned int ShaderID;

	int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const char* src);
	std::string GetFileContents(const std::string& file);
};
#endif // !SHADER_CLASS
