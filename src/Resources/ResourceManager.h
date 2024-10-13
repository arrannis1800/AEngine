#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

#include "Structs/AGState.h"
#include "Render/ShaderProgram.h"
#include "Render/Texture.h"


class AResourceManager
{
public:
	std::shared_ptr<AShaderProgram> LoadShaderProgram(const std::string& shaderName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	std::shared_ptr<AShaderProgram> GetShaderProgram(const std::string& shaderName);

	std::shared_ptr<ATexture> LoadTexture(const std::string& textureName, const std::string& texturePath);
	std::shared_ptr<ATexture> GenerateTexture(const std::string& textureName, int width, int height, int channels, const unsigned char* pixels);
	std::shared_ptr<ATexture> GetTexture(const std::string& textureName);

private:
	std::string GetFileData(const std::string& filePath);
	std::map<std::string, std::shared_ptr<AShaderProgram>> m_shaderPrograms;
	std::map<std::string, std::shared_ptr<ATexture>> m_textures;
};

#endif // !RESOURCE_MANAGER_H
