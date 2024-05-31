#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <math.h>

#include "MacrosLibrary.h"
#include "LevelSettings.h"

static int position = 0;

class ALevel
{
public:
	ALevel()
	{
		LevelSettings = new ALevelSettings;
		LevelSettings->Height = 500;
		LevelSettings->Width = 500;
	}

	~ALevel()
	{
		delete LevelSettings;
	}

	void Init()
	{
		if(!LevelSettings)
	        AppTerminate();

		Log(ELogType::INFO, "Level \"%s\" init success\n", LevelSettings->name.c_str());
	}

	void Tick()
	{
		int red   = (uint8_t)(sin(position * 0.3) * 127 + 128);
		int green = (uint8_t)(sin(position * 0.3 + 2 * M_PI / 3) * 127 + 128);
		int blue  = (uint8_t)(sin(position * 0.3 + 4 * M_PI / 3) * 127 + 128);

		LevelSettings->BackGroundColor = (red << 8*3) | (green << 8*2) | (blue << 8*1) | (0xff << 8*0);

		++position;
	}

	ALevelSettings* GetLevelSettings() const
	{
		return LevelSettings;
	}
private:
	ALevelSettings* LevelSettings;
	// std::vector<AObject*> Objects;
};

#endif