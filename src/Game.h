#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Level.h"

class AGame
{
public:
	AGame();

	virtual ~AGame() = default;

	void InitLevels();

	virtual void Init();

	virtual void Tick();

	ALevel* GetCurrentLevel() const;
protected:
	std::vector<ALevel*> m_levels;
	ALevel* m_pCurrentLevel;
};

#endif