#include "Render/Texture.h"

#include "MacrosLibrary.h"

ATexture::ATexture(int width, int height, const unsigned char* pixels, int channels) : m_width(width), m_height(height)
{
	GLenum m_gl_mode;
	switch (channels)
	{
	case 3:
		m_ColorMode = EColorMode::RGB; 
		m_gl_mode = GL_RGB;
		break;
	case 4:
		m_ColorMode = EColorMode::RGBA;
		m_gl_mode = GL_RGBA;
		break;
	default:
		Log(ELogType::ERROR,"unknown format channels % d\n", channels);
		m_ColorMode = EColorMode::RGB;
		m_gl_mode = GL_RGB;
		break;
	}

	glGenTextures(1, &m_ID);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, m_gl_mode, m_width, m_height, 0, m_gl_mode, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, 0);
}

ATexture::~ATexture()
{
	glDeleteTextures(1, &m_ID);
}

ATexture::ATexture(ATexture&& texture) noexcept
{
	m_ID = texture.m_ID;
	m_height = texture.m_height;
	m_width = texture.m_width;
	m_ColorMode = texture.m_ColorMode;

	texture.m_ID = 0;
	texture.m_height = 0;
	texture.m_width = 0;
	texture.m_ColorMode = EColorMode::NONE;
}

ATexture& ATexture::operator=(ATexture&& texture) noexcept
{
	m_ID = texture.m_ID;
	m_height = texture.m_height;
	m_width = texture.m_width;
	m_ColorMode = texture.m_ColorMode;

	texture.m_ID = 0;
	texture.m_height = 0;
	texture.m_width = 0;
	texture.m_ColorMode = EColorMode::NONE;

	return *this;
}

void ATexture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
