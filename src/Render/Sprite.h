#ifndef SPRITE_H
#define SPRITE_H

#include <memory>
#include "Render/Texture.h"
#include "Render/ShaderProgram.h"
#include "Math/Mat4.h"

class ASprite
{
public:
	ASprite() = delete;
	ASprite(const std::shared_ptr<ATexture> pTexture,
			const std::shared_ptr<AShaderProgram> pShaderProgram);
	~ASprite();

	ASprite(const ASprite&) = delete;
	ASprite& operator=(const ASprite&) = delete;

	void Render(AMat4x4& ProjMat, AMat4x4& ModelMat);

private:
	std::shared_ptr<ATexture> m_pTexture;
	std::shared_ptr<AShaderProgram> m_pShaderProgram;
	uint32_t m_vao = 0;
	uint32_t m_vertexCoordsVBO = 0;
	uint32_t m_textureCoordsVBO = 0;
};

#endif // !SPRITE_H
