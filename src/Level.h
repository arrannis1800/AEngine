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
		m_pLevelSettings = &config::m_pLevelSettings;
		AObject* obj = new AObject;
		objects.push_back(obj);
	}

	void Init();

	void Tick();

	ALevelSettings* GetLevelSettings() const;

	const std::vector<AObject*>& GetLevelObjects() const;
private:
	float position = 0;
	ALevelSettings* m_pLevelSettings;
	std::vector<AObject*> objects;
	std::vector<AObject*> refreshableObjects;
	// std::vector<AWidget*> Widgets;
};

#endif