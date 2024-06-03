#ifndef ENGINE_H
#define ENGINE_H

#include <chrono>

#include "World.h"
#include "Renderer.h"

#include <SDL.h>

class AEngine
{
private:
	friend int SDL_main(int, char**);
	AEngine(AWorld* World);

	void SetVideoParams();

	void Init();

	void Tick();

	void Run();

	void Finish();

	void Start();

	void CalculateDeltaTime();
public:

	float GetDeltaTime();

private:
	AWorld* World = nullptr;
	AWindow* Window = nullptr;
	AVideoParams* VideoParams;
	float DeltaTime;
	std::chrono::time_point<std::chrono::steady_clock> LastTime;
};

extern AEngine* gEngineInstance;

#endif