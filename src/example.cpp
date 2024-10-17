#include "Structs/AGState.h"
#include "Game.h"

class ACustomGame : public AGame
{
public:
	ACustomGame()
	{
		ALevel* level = new ALevel;
		Levels.push_back(level);
	}
} CustomGame;

AGGame AGGameController =
{
	.Game = reinterpret_cast<AGame*>(&CustomGame),
};