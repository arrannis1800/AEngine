#include "Structs/AGState.h"
#include "Game.h"

class ACustomGame : public AGame
{
public:
	ACustomGame()
	{
		ALevel* level = new ALevel;
		m_levels.push_back(level);
	}
} CustomGame;

AGGame gGameHandler =
{
	.pGame = reinterpret_cast<AGame*>(&CustomGame),
};