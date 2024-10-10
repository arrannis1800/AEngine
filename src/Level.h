#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "Structs/LevelSettings.h"
#include "Object.h"
#include "Config.h"

class ALevel
{
public:
	ALevel()
	{
		LevelSettings = &config::LevelSettings;
		AObject* obj = new AObject;
		Objects.push_back(obj);
	}

	void Init();

	void Tick();

	ALevelSettings* GetLevelSettings() const;

	const std::vector<AObject*>& GetLevelObjects() const;
private:
	float position = 0;
	ALevelSettings* LevelSettings;
	std::vector<AObject*> Objects;
	std::vector<AObject*> RefreshableObjects;
	// std::vector<AWidget*> Widgets;
};

#endif