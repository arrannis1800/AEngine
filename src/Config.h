#ifndef CONFIG_H
#define CONFIG_H

//#include "SDL.h"

#include "Structs/AVideoParams.h"
#include "Structs/LevelSettings.h"
#include "Math/AVector.h"

namespace config {
	inline AVideoParams VideoParams =
	{
		.Width = 700,
		.Height = 700,
	};

	inline ALevelSettings LevelSettings =
	{
		.Height = 1000.0f,
		.Width = 1000.0f,
		.CameraVisibleHeight = 100.0f,
		.CameraVisibleRatio = 16.0f / 9.0f,
		.CameraPosition = AVector2(),
		.name = "first_level",
		.BackGroundColor = 0,
	};
}
#endif