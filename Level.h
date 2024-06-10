#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "Structs/LevelSettings.h"
#include "Config.h"

class ALevel
{
public:
	ALevel()
	{
		LevelSettings = &config::LevelSettings;
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