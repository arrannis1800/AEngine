#ifndef CONFIG_H
#define CONFIG_H


#include "Structs/AVideoParams.h"
#include "Structs/LevelSettings.h"
#include "Math/AVector.h"

namespace config {
	inline AVideoParams pVideoParams =
	{
		.width = 700,
		.height = 700,
	};

	inline ALevelSettings m_pLevelSettings =
	{
		.height = 1000.0f,
		.width = 1000.0f,
		.cameraVisibleHeight = 100.0f,
		.cameraVisibleRatio = 16.0f / 9.0f,
		.cameraPosition = AVector2(),
		.name = "first_level",
		.backGroundColor = 0,
	};
}
#endif