#include "Render/ShaderProgram.h"

#include "glad/glad.h"

#include "MacrosLibrary.h"

AShaderProgram::AShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	m_ID = glCreateProgram();
	if (!CreateShader(EShaderType::VERTEX, vertexShader))
	{
		AppTerminate();
	}
	if (!CreateShader(EShaderType::FRAGMENT, fragmentShader))
	{
		AppTerminate();
	}
	glLinkProgram(m_ID);

	int success;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
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

void AShaderProgram::Use() const
{
	glUseProgram(m_ID);
}

void AShaderProgram::SetInt(const std::string& name, const uint32_t value)
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void AShaderProgram::SetMatrix4(const std::string& name, const AMat4x4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, matrix.GetPtr());
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

bool AShaderProgram::CreateShader(EShaderType type, const std::string& shader)
{
	GLuint shaderId = 0;
	switch (type)
	{
	case EShaderType::VERTEX:
		shaderId = glCreateShader(GL_VERTEX_SHADER);
		break;
	case EShaderType::FRAGMENT:
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		break;
	}
	 
	const char* code = shader.c_str();
	glShaderSource(shaderId, 1, &code, nullptr);
	glCompileShader(shaderId);
	if (!CheckShaderError(shaderId))
		return false;

	glAttachShader(m_ID, shaderId);

	glDeleteShader(shaderId);
	return true;
}

bool AShaderProgram::CheckShaderError(uint32_t shader)
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
