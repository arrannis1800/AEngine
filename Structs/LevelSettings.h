#ifndef LEVELSETTINGS_H
#define LEVELSETTINGS_H

#include <cstdint>

struct ALevelSettings
{
	int Height;
	int Width;
	std::string name = "first level";
	uint32_t BackGroundColor;
};

#endif