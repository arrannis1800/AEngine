#include "ShaderProgram.h"
#include "ShaderProgram.h"
#include "ShaderProgram.h"
#include "ShaderProgram.h"
#include "ShaderProgram.h"
#include "ShaderProgram.h"
#include "ShaderProgram.h"

#include "Render/OpenGL/ShaderProgram.h"
#include "MacrosLibrary.h"

AShaderProgram::AShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	m_ID = glCreateProgram();
	if (!CreateShader(GL_VERTEX_SHADER, vertexShader))
	{
		AppTerminate();
	}
	if (!CreateShader(GL_FRAGMENT_SHADER, fragmentShader))
	{
		AppTerminate();
	}
	glLinkProgram(m_ID);

	int success;
	glGetProgramiv(m_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(m_ID, 512, nullptr, infoLog);
		Log(ELogType::ERROR, "SHADER: %s\n", infoLog);
		AppTerminate();
	}
	else
	{
		m_bIsCompiled = true;
	}

}

AShaderProgram::~AShaderProgram()
{
	glDeleteProgram(m_ID);
}

void AShaderProgram::use() const
{
	glUseProgram(m_ID);
}

AShaderProgram::AShaderProgram(AShaderProgram&& other) noexcept
{
	m_ID = other.m_ID;
	m_bIsCompiled = other.m_bIsCompiled;

	other.m_ID = 0;
	other.m_bIsCompiled = false;
}

AShaderProgram& AShaderProgram::operator=(AShaderProgram&& other) noexcept
{
	glDeleteProgram(m_ID);

	m_ID = other.m_ID;
	m_bIsCompiled = other.m_bIsCompiled;

	other.m_ID = 0;
	other.m_bIsCompiled = false;

	return *this;
}

bool AShaderProgram::CreateShader(GLenum type, const std::string& shader)
{
	GLuint shaderId = glCreateShader(type);
	const char* code = shader.c_str();
	glShaderSource(shaderId, 1, &code, nullptr);
	glCompileShader(shaderId);
	if (!CheckShaderError(shaderId))
		return false;

	glAttachShader(m_ID, shaderId);

	glDeleteShader(shaderId);
	return true;
}

bool AShaderProgram::CheckShaderError(GLuint shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		Log(ELogType::ERROR, "SHADER: %s\n", infoLog);
		return false;
	}
	return true;
}
