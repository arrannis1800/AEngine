#ifndef AGSTATE_H
#define AGSTATE_H

#include <string>
#include "Game.h"


class AEngine;
class AResourceManager;
struct AGGame
{
	AGame* pGame;
};
extern AGGame gGameHandler;

struct AGState
{
private:
	friend int main(int, char**);
	std::string path;
	AEngine* pEngine = nullptr;
	AResourceManager* pResourceManager = nullptr;
	AGGame* pGameHandler = &gGameHandler;
public:
	std::string& GetPath() { return path; };
	AEngine* GetEngine() { return pEngine; };
	AResourceManager* GetResourceManager() { return pResourceManager; };
};

inline AGState gState;

#endif // !AGSTATE_H
