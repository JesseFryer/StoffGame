#include "GLAD\glad.h"
#include "Shader.h"
#include <fstream>
#include <iostream>

Shader::Shader()
{
	m_ID = 0;
}
void Shader::Init(const std::string& filepath)
{
	std::string srcString;
	std::ifstream shaderFile(filepath, std::ios::in, std::ios::binary);
	if (shaderFile)
	{
		shaderFile.seekg(0, std::ios::end);
		srcString.resize(shaderFile.tellg());
		shaderFile.seekg(0, std::ios::beg);
		shaderFile.read(&srcString[0], srcString.size());
		shaderFile.close();
	}
	else std::cout << "could not open shader file." << std::endl;

	ShaderSource src = ParseSourceCode(srcString);
    const char* vShaderCode = src.vertSrc.c_str();
    const char* fShaderCode = src.fragSrc.c_str();

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    checkCompileErrors(vertex, "VERTEX");
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "VERTEX");

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    checkCompileErrors(m_ID, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
void Shader::Use()
{
	glUseProgram(m_ID);
}
void Shader::SetMat4(const std::string& name, glm::mat4 value)
{
	GLuint location = glGetUniformLocation(m_ID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}
unsigned int Shader::GetID()
{
	return m_ID;
}
ShaderSource Shader::ParseSourceCode(const std::string& shaderSource)
{
	ShaderSource src;
	size_t splitIndex = shaderSource.rfind("#version");
	src.vertSrc = shaderSource.substr(0, splitIndex);
	src.fragSrc = shaderSource.substr(splitIndex);
	return src;
}
void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
