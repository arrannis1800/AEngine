#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>

#include "Structs/EShaderTypes.h"
#include "Math/Mat4.h"

class AShaderProgram
{
public:
	AShaderProgram() = delete;
	AShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	~AShaderProgram();

	bool IsCompiled() const { return m_bIsCompiled; }
	void Use() const;
	void SetInt(const std::string& name, const uint32_t value);
	void SetMatrix4(const std::string& name, const AMat4x4& matrix);

	AShaderProgram(AShaderProgram&) = delete;
	AShaderProgram& operator=(const AShaderProgram&) = delete;

	AShaderProgram(AShaderProgram&& other) noexcept;
	AShaderProgram& operator=(AShaderProgram&& other) noexcept;
private:
	bool CreateShader(EShaderType type, const std::string& shader);
	bool CheckShaderError(uint32_t shader);

	uint32_t m_ID = 0;
	bool m_bIsCompiled = false;
};

#endif // !SHADER_PROGRAM_H
