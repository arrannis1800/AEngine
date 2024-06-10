#include <vector>

#include "Game.h"

#include "MacrosLibrary.h"

#include "Level.h"


AGame::AGame()
{
	ALevel* level = new ALevel;
	Levels.push_back(level);
}

void AGame::InitLevels()
{
	if(Levels.size() == 0)
		AppTerminate();
	for (auto& Level : Levels)
	{
		Level->Init();
	}
	Log(ELogType::INFO, "All levels init success\n");
}

void AGame::Init()
{
	InitLevels();

	CurrentLevel = Levels[0];

	Log(ELogType::INFO, "Game init success\n");
}

void AGame::Tick()
{
	// TODO: GameMode->Tick
	CurrentLevel->Tick();
}

ALevel* AGame::GetCurrentLevel() const
{
	return CurrentLevel;
}

