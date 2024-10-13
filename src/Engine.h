#ifndef ENGINE_H
#define ENGINE_H

#include <chrono>

#include "Game.h"
#include "Render/Renderer.h"

class AEngine
{
private:
	friend int main(int, char**);
	friend struct AGState;
	AEngine() = default; 
	AEngine(AGame* Game);

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

private:
	AGame* Game = nullptr;
	ARenderer* Window = nullptr;
	AVideoParams* VideoParams = nullptr;
	float DeltaTime = 0;
	std::chrono::time_point<std::chrono::steady_clock> LastTime;
};

#endif