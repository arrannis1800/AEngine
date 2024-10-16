#ifndef AGSTATE_H
#define AGSTATE_H

#include <string>
#include "Game.h"


class AEngine;
class AResourceManager;
struct AGGame
{
	AGame* Game;
};
extern AGGame AGGameController;

struct AGState
{
private:
	friend int main(int, char**);
	std::string path;
	AEngine* engine = nullptr;
	AResourceManager* ResourceManager = nullptr;
	AGGame* GameController = &AGGameController;
public:
	std::string& GetPath() { return path; };
	AEngine* GetEngine() { return engine; };
	AResourceManager* GetResourceManager() { return ResourceManager; };
};

inline AGState gState;

#endif // !AGSTATE_H
