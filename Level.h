#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "Structs/LevelSettings.h"

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

	void Init();

	void Tick();

	ALevelSettings* GetLevelSettings() const;
private:
	float position = 0;
	ALevelSettings* LevelSettings;
	// std::vector<AObject*> Objects;
};

#endif