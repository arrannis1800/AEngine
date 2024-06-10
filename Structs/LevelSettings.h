#ifndef LEVELSETTINGS_H
#define LEVELSETTINGS_H

#include <cstdint>
#include <string>

struct ALevelSettings
{
	int Height;
	int Width;
	int CameraVisibleHeight;
	int CameraVisibleRatio = 16.0f / 9.0f;
	std::string name;
	uint32_t BackGroundColor;
};

#endif