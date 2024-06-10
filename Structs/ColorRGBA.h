#ifndef COLOR_RGBA_H
#define COLOR_RGBA_H value

struct ColorRGBA
{
	ColorRGBA() = default;

	ColorRGBA(uint32_t color)
	{
		r = (color >> (8*3)) & 0xff;
		g = (color >> (8*2)) & 0xff;
		b = (color >> (8*1)) & 0xff;
		a = (color >> (8*0)) & 0xff;
	}

	uint32_t toUInt32()
	{
		return (r << 24) | (g << 16) | (b << 8) | a;
	};

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

#endif