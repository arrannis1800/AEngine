#include <math.h>

#include "Render/Shape.h"
#include "Structs/AGState.h"
#include "Resources/ResourceManager.h"

AShape AShape::DrawCircle(const int radius, ColorRGBA color)
{
	int textureWidth = radius * 2;
	int pixelsSize = textureWidth * textureWidth;
	unsigned char* pixels = new unsigned char[pixelsSize * 4];
	for (int i = 0; i < pixelsSize; ++i)
	{
		int x = i / textureWidth;
		int y = i % textureWidth;
		if (sqrtf((x - radius) * (x - radius) + (y - radius) * (y - radius)) < radius)
		{
			pixels[i * 4 + 0] = color.r;
			pixels[i * 4 + 1] = color.g;
			pixels[i * 4 + 2] = color.b;
			pixels[i * 4 + 3] = color.a;
		}
		else
		{
			pixels[i * 4 + 0] = 0x00;
			pixels[i * 4 + 1] = 0x00;
			pixels[i * 4 + 2] = 0x00;
			pixels[i * 4 + 3] = 0x00;
		}

	}
	
	return AShape(EForm::Circle, color, textureWidth, textureWidth, pixels);
}

std::string AShape::CreateTextureFromShape(AShape& Shape)
{
	std::string m_textureName = "*Cirle_" + std::to_string(Shape.m_width) +"x" + std::to_string(Shape.m_height)  + "_c" + Shape.m_color.toString();
	if(!gState.GetResourceManager()->GetTexture(m_textureName))
		gState.GetResourceManager()->CreateTexture(m_textureName, Shape.m_width, Shape.m_height, 4, Shape.m_pPixels);
	return m_textureName;
}

AShape::~AShape()
{
	delete[] m_pPixels;
}
