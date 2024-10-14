#ifndef SHAPE_H
#define SHAPE_H

#include <string>

#include "Structs/EForm.h"
#include "Structs/ColorRGBA.h"

class AShape
{
public:
	static AShape DrawCircle(const int radius, ColorRGBA color);
	static std::string CreateTextureFromShape(AShape& Shape);
	~AShape();
private:
	AShape() = delete;
	AShape(EForm form, ColorRGBA color, int width, int height, unsigned char* pixels) : m_form(form), m_color(color), m_width(width), m_height(height), m_pixels(pixels) {}

	unsigned char* m_pixels;
	int m_width;
	int m_height;
	ColorRGBA m_color;
	EForm m_form;
};

#endif // !SHAPE_H
