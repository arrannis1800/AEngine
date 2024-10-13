#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

#include "Structs/AGState.h"
#include "Render/ShaderProgram.h"


class AResourceManager
{
public:
	std::shared_ptr<AShaderProgram> LoadShaderProgram(const std::string& shaderName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	std::shared_ptr<AShaderProgram> GetShaderProgram(const std::string& shaderName);
private:
	std::string GetFileData(const std::string& filePath);
	std::map<std::string, std::shared_ptr<AShaderProgram>> m_shaderPrograms;
};

#endif // !RESOURCE_MANAGER_H
