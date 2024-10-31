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
		
	}
	virtual ~ALevel() = default;

	virtual void Init();

	virtual void Tick();

	ALevelSettings* GetLevelSettings() const;

	const std::vector<AObject*>& GetLevelObjects() const;
private:
	float position = 0;
	ALevelSettings* m_pLevelSettings;
protected:
	std::vector<AObject*> m_objects;
	std::vector<AObject*> m_refreshableObjects;
	// std::vector<AWidget*> Widgets;
};

#endif