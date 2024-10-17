#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Level.h"

class AGame
{
public:
	AGame();

	void InitLevels();

	void Init();

	void Tick();

	ALevel* GetCurrentLevel() const;
protected:
	std::vector<ALevel*> Levels;
	ALevel* CurrentLevel;
};

#endif