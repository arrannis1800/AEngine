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
#include "Render/Sprite.h"


class AResourceManager
{
public:
	std::shared_ptr<AShaderProgram> LoadShaderProgram(const std::string& shaderName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	std::shared_ptr<AShaderProgram> GetShaderProgram(const std::string& shaderName);

	std::shared_ptr<ATexture> LoadTexture(const std::string& m_textureName, const std::string& texturePath);
	std::shared_ptr<ATexture> CreateTexture(const std::string& m_textureName, int width, int height, int channels, const unsigned char* pixels);
	std::shared_ptr<ATexture> GetTexture(const std::string& m_textureName);

	std::shared_ptr<ASprite> LoadSprite(const std::string& spriteName, const std::string& m_textureName, const std::string& shaderName);
	std::shared_ptr<ASprite> GetSprite(const std::string& spriteName);

private:
	std::string GetFileData(const std::string& filePath);
	std::map<std::string, std::shared_ptr<AShaderProgram>> m_shaderPrograms;
	std::map<std::string, std::shared_ptr<ATexture>> m_textures;
	std::map<std::string, std::shared_ptr<ASprite>> m_sprites;
};

#endif // !RESOURCE_MANAGER_H
