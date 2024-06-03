#ifndef CONFIG_H
#define CONFIG_H

#include "Structs/AVideoParams.h"

namespace config {
	static AVideoParams VideoParams = 
	{
		.Width = 700,
		.Height = 700,
		.Flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,

		.FontPath = "fonts/times.ttf",
		.FontSize = 24,
	};
}
#endif