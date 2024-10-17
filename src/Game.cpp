#include <vector>

#include "Game.h"

#include "MacrosLibrary.h"

#include "Level.h"


AGame::AGame()
{
}

void AGame::InitLevels()
{
	if(m_levels.size() == 0)
		AppTerminate();
	for (auto& Level : m_levels)
	{
		Level->Init();
	}
	Log(ELogType::INFO, "All levels init success\n");
}

void AGame::Init()
{
	InitLevels();

	m_pCurrentLevel = m_levels[0];

	Log(ELogType::INFO, "Game init success\n");
}

void AGame::Tick()
{
	// TODO: GameMode->Tick
	m_pCurrentLevel->Tick();
}

ALevel* AGame::GetCurrentLevel() const
{
	return m_pCurrentLevel;
}

