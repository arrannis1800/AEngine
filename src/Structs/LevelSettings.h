#ifndef LEVELSETTINGS_H
#define LEVELSETTINGS_H

#include <cstdint>
#include <string>

#include "Math/AVector.h"

struct ALevelSettings
{
	float height;
	float width;
	float cameraVisibleHeight = height;
	float cameraVisibleRatio = 16.0f / 9.0f;
	AVector2 cameraPosition;
	std::string name = "Test";
	uint32_t backGroundColor;
};

#endif