#ifndef AGSTATE_H
#define AGSTATE_H

#include <string>
class AEngine;
class AResourceManager;

struct AGState
{
private:
	friend int main(int, char**);
	std::string path;
	AEngine* engine = nullptr;
	AResourceManager* ResourceManager = nullptr;
public:
	std::string& GetPath() { return path; };
	AEngine* GetEngine() { return engine; };
	AResourceManager* GetResourceManager() { return ResourceManager; };
};

inline AGState gState;

#endif // !AGSTATE_H
