#ifndef LEVELSETTINGS_H
#define LEVELSETTINGS_H

#include <cstdint>
#include <string>

#include "Math/AVector.h"

struct ALevelSettings
{
	float Height;
	float Width;
	float CameraVisibleHeight = Height;
	float CameraVisibleRatio = 16.0f / 9.0f;
	AVector2 CameraPosition;
	std::string name = "Test";
	uint32_t BackGroundColor;
};

#endif