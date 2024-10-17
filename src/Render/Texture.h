#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdint>

#include "Structs/EColorModes.h"

class ATexture
{
public:
	ATexture() = delete;
	ATexture(int width, int height, const unsigned char* pixels, int channels = 4);
	~ATexture();

	ATexture(const ATexture&) = delete;
	ATexture& operator=(const ATexture&) = delete;

	ATexture(ATexture&& texture) noexcept;
	ATexture& operator=(ATexture&& texture) noexcept;

	void Bind();
private:
	uint32_t m_ID;
	int m_width;
	int m_height;
	EColorMode m_colorMode;
};

#endif // !TEXTURE_H
