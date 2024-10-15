#include <math.h>

#include "Render/Shape.h"
#include "Structs/AGState.h"
#include "Resources/ResourceManager.h"

AShape AShape::DrawCircle(const int radius, ColorRGBA color)
{
	int texture_width = radius * 2;
	int pixels_size = texture_width * texture_width;
	unsigned char* pixels = new unsigned char[pixels_size * 4];
	for (int i = 0; i < pixels_size; ++i)
	{
		int x = i / texture_width;
		int y = i % texture_width;
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
	
	return AShape(EForm::Circle, color, texture_width, texture_width, pixels);
}

std::string AShape::CreateTextureFromShape(AShape& Shape)
{
	std::string texture_name = "*Cirle_" + std::to_string(Shape.m_width) +"x" + std::to_string(Shape.m_height)  + "_c" + Shape.m_color.toString();
	if(!gState.GetResourceManager()->GetTexture(texture_name))
		gState.GetResourceManager()->CreateTexture(texture_name, Shape.m_width, Shape.m_height, 4, Shape.m_pixels);
	return texture_name;
}

AShape::~AShape()
{
	delete[] m_pixels;
}
