#ifndef CONFIG_H
#define CONFIG_H

#include "SDL.h"

#include "Structs/AVideoParams.h"
#include "Structs/LevelSettings.h"

namespace config {
	static AVideoParams VideoParams = 
	{
		.Width = 700,
		.Height = 700,
		.Flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,

		.FontPath = "fonts/times.ttf",
		.FontSize = 24,
	};

	static ALevelSettings LevelSettings =
	{
		.Height = 1000,
		.Width = 1000,
		.CameraVisibleHeight = 100,
		.CameraVisibleRatio = 16.0f / 9.0f,
		.name = "first level",
		.BackGroundColor = 0,
	};
}
#endif