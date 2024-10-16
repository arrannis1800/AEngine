#include "Structs/AGState.h"
#include "Game.h"

class ACustomGame : public AGame
{

} CustomGame;

AGGame AGGameController =
{
	.Game = reinterpret_cast<AGame*>(&CustomGame),
};