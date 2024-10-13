#ifndef AGSTATE_H
#define AGSTATE_H

#include <string>
#include "Engine.h"

struct AGState
{
private:
	friend int main(int, char**);
	std::string path;
	AEngine* engine;
public:
	std::string& GetPath() { return path; }
	AEngine* GetEngine() { return engine; }
};

inline AGState gState;

#endif // !AGSTATE_H
