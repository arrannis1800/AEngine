#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Structs/AVideoParams.h"
#include "MacrosLibrary.h"

#include "Level.h"

class AWorld
{
public:
	AWorld()
	{
		ALevel* level = new ALevel;
		Levels.push_back(level);
	}

	void InitLevels()
	{
		if(Levels.size() == 0)
			AppTerminate();
		for (auto& Level : Levels)
		{
			Level->Init();
		}
		Log(ELogType::INFO, "All levels init success\n");
	}

	void Init()
	{
		InitLevels();

		CurrentLevel = Levels[0];

		Log(ELogType::INFO, "World init success\n");
	}

	void Tick()
	{
		CurrentLevel->Tick();
	}

	ALevel* GetCurrentLevel() const
	{
		return CurrentLevel;
	}
private:
	std::vector<ALevel*> Levels;
	ALevel* CurrentLevel;
};

#endif