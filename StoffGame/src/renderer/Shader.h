#pragma once

#include <string>
#include "GLM\glm.hpp"

struct ShaderSource
{
	std::string vertSrc;
	std::string fragSrc;
};

class Shader
{
public:
	Shader();
	void Init(const std::string& filepath);
	void Use();
	void SetMat4(const std::string& name, glm::mat4 value);
	unsigned int GetID();

private:
	unsigned int m_ID;

private:
	ShaderSource ParseSourceCode(const std::string& shaderSource);
	void checkCompileErrors(unsigned int shader, std::string type);
};
