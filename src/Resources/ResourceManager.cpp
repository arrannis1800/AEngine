#include "Resources/ResourceManager.h"

#include "MacrosLibrary.h"

std::shared_ptr<AShaderProgram> AResourceManager::LoadShaderProgram(const std::string& shaderName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	std::string vertexShader = GetFileData(vertexShaderPath);
	if (vertexShader.empty())
	{
		Log(ELogType::LT_ERROR, "vertex shader data wasn't loaded: %s\n", vertexShaderPath.c_str());
		return nullptr;
	}
	std::string fragmentShader = GetFileData(fragmentShaderPath);
	if (fragmentShader.empty())
	{
		Log(ELogType::LT_ERROR, "fragment shader data wasn't loaded: %s\n", fragmentShaderPath.c_str());
		return nullptr;
	}
	std::shared_ptr<AShaderProgram> sharedProgram = std::make_shared<AShaderProgram>(vertexShader, fragmentShader);
	if (!sharedProgram->IsCompiled())
	{
		Log(ELogType::LT_ERROR, "shader program not created\n\tvertex: %s\n\tfragment: %s\n", vertexShaderPath.c_str(), fragmentShaderPath.c_str());
		return nullptr;
	}

	m_shaderPrograms.emplace(shaderName, sharedProgram);

	return sharedProgram;
}

std::shared_ptr<AShaderProgram> AResourceManager::GetShaderProgram(const std::string& shaderName)
{
	auto it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end())
	{
		return it->second;
	}
	else
	{
		Log(ELogType::LT_ERROR, "shader program didn't find: %s\n", shaderName.c_str());
		return nullptr;
	}
}

std::shared_ptr<ATexture> AResourceManager::LoadTexture(const std::string& m_textureName, const std::string& texturePath)
{
	return std::shared_ptr<ATexture>();
}

std::shared_ptr<ATexture> AResourceManager::CreateTexture(const std::string& m_textureName, int width, int height, int channels, const unsigned char* pixels)
{
	if (!pixels)
	{
		Log(ELogType::LT_ERROR, "pixels for texture %s not provided\n", m_textureName.c_str());
		return nullptr;
	}

	std::shared_ptr<ATexture> texture = std::make_shared<ATexture>(width, height, pixels, channels);

	if (!texture)
	{
		Log(ELogType::LT_ERROR, "texture %s not created\n", m_textureName.c_str());
		return nullptr;
	}
	m_textures.emplace(m_textureName, texture);

	return texture;
}

std::shared_ptr<ATexture> AResourceManager::GetTexture(const std::string& m_textureName)
{
	auto it = m_textures.find(m_textureName);
	if (it != m_textures.end())
	{
		return it->second;
	}
	else
	{
		Log(ELogType::LT_ERROR, "texture %s not found\n", m_textureName.c_str());
		return nullptr;
	}
}

std::shared_ptr<ASprite> AResourceManager::LoadSprite(const std::string& spriteName, const std::string& m_textureName, const std::string& shaderName)
{
	auto shader = GetShaderProgram(shaderName);
	if(!shader)
	{
		Log(ELogType::LT_ERROR, "shader %s not found to create sprite\n", shaderName.c_str());
		return nullptr;
	}

	auto texture = GetTexture(m_textureName);
	if (!texture)
	{
		Log(ELogType::LT_ERROR, "texture %s not found to create sprite\n", m_textureName.c_str());
		return nullptr;
	}

	std::shared_ptr<ASprite> Sprite = std::make_shared<ASprite>(texture, shader);
	if (!Sprite)
	{
		Log(ELogType::LT_ERROR, "sprite %s not created\n", spriteName.c_str());
		return nullptr;
	}

	m_sprites.emplace(shaderName, Sprite);

	return Sprite;

}

std::shared_ptr<ASprite> AResourceManager::GetSprite(const std::string& spriteName)
{
	auto it = m_sprites.find(spriteName);
	if (it != m_sprites.end())
	{
		return it->second;
	}
	else
	{
		Log(ELogType::LT_ERROR, "sprite %s not found\n", spriteName.c_str());
		return nullptr;
	}
}

std::string AResourceManager::GetFileData(const std::string& filePath)
{
	std::ifstream f;
	f.open(gState.GetPath() + "/" + filePath.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		Log(ELogType::LT_ERROR, "file %s not loaded\n", filePath.c_str());
		return std::string();
	}
	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}
