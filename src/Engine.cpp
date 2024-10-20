#include "Engine.h"
#include "MacrosLibrary.h"
#include "Config.h"

AEngine* gEngineInstance = nullptr;

AEngine::AEngine(AGame* game) : game(game)
{
	gEngineInstance = this;
};

void AEngine::SetVideoParams()
{
	pVideoParams = &config::pVideoParams;
	Log(ELogType::LT_INFO, "Video Prarms set\n\tWidth = %d\n\tHeight = %d\n", pVideoParams->width, pVideoParams->height);
}

void AEngine::Init()
{
	{
		window = new ARenderer();
		if (!window)
		{
			AppTerminate();
		}
		SetVideoParams();
		window->Init(pVideoParams);
	}

	game->Init();

	CalculateDeltaTime();
	
	Log(ELogType::LT_INFO, "Engine init success\n");
}

void AEngine::Tick()
{
	CalculateDeltaTime();
	game->Tick();
	window->Render(game);
}

void AEngine::Run()
{
	bool quit = false;

	while(!window->ShouldClose())
	{
		Tick();
	}
}

void AEngine::Finish()
{
	window->finish();
	if(window)
		delete window;
}

void AEngine::Start()
{
	Init();

	Run();

	Finish();
}

void AEngine::CalculateDeltaTime()
{
	std::chrono::time_point<std::chrono::steady_clock> Now = std::chrono::steady_clock::now();
	DeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(Now - LastTime).count() / 1000.0f / 1000.0f;
	LastTime = Now;
}

float AEngine::GetDeltaTime()
{
	return DeltaTime;
}

int AEngine::GetFPS()
{
	return 1 / DeltaTime;
}