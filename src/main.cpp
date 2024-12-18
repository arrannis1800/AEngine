#include "Engine.h"
#include "Game.h"
#include "Config.h"
#include "Structs/AGState.h"
#include "Resources/ResourceManager.h"


int main(int argc, char* args[])
{
	(void)argc;
	std::string m_path(args[0]);
	size_t position = m_path.find_last_of('/\\');
	gState.path = m_path.substr(0, position);
	AGame game;
	AEngine pEngine(gState.pGameHandler->pGame);
	AResourceManager pResourceManager;
	gState.pResourceManager = &pResourceManager;
	gState.pEngine = &pEngine;
	gState.GetEngine()->Start();

	return 0;
}
