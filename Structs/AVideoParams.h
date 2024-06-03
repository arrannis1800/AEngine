#ifndef VIDEOPARAMS_H
#define VIDEOPARAMS_H

struct AVideoParams
{
	int Width;
	int Height;
	size_t Flags;

	const char* FontPath = "fonts/times.ttf";
	size_t FontSize;
};

#endif