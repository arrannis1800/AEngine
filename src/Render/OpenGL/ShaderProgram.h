#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>

#include "glad/glad.h"

class AShaderProgram
{
public:
	AShaderProgram() = delete;
	AShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	~AShaderProgram();

	bool IsCompiled() const { return m_bIsCompiled; }
	void use() const;

	AShaderProgram(AShaderProgram&) = delete;
	AShaderProgram& operator=(const AShaderProgram&) = delete;

	AShaderProgram(AShaderProgram&& other) noexcept;
	AShaderProgram& operator=(AShaderProgram&& other) noexcept;
private:
	bool CreateShader(GLenum type, const std::string& shader);
	bool CheckShaderError(GLuint shader);

	GLuint m_ID = 0;
	bool m_bIsCompiled = false;
};

#endif // !SHADER_PROGRAM_H
