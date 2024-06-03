#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Structs/AVideoParams.h"
#include "MacrosLibrary.h"

#include "Level.h"

class AGame
{
public:
	AGame()
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

		Log(ELogType::INFO, "Game init success\n");
	}

	void Tick()
	{
		// TODO: GameMode->Tick
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