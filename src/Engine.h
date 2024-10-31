#ifndef ENGINE_H
#define ENGINE_H

#include <chrono>

#include "Game.h"
#include "Callbacks.h"
#include "Render/Renderer.h"

class AEngine
{
private:
	friend int main(int, char**);
	friend struct AGState;
	friend class AWindow;
	AEngine() = default; 
	AEngine(AGame* game);

	void SetVideoParams();

	void Init();

	void Tick();

	void Run();

	void Finish();

	void Start();

	void CalculateDeltaTime();

public:

	float GetDeltaTime();

	int GetFPS();
	ACallback* GetCallback();

private:
	AGame* pGame = nullptr;
	ARenderer* pWindow = nullptr;
	AVideoParams* pVideoParams = nullptr;
	ACallback* pCallback;
	float DeltaTime = 0;
	std::chrono::time_point<std::chrono::steady_clock> LastTime;
};

#endif