#include "Engine.h"
#include "MacrosLibrary.h"
#include "Config.h"

AEngine* gEngineInstance = nullptr;

AEngine::AEngine(AGame* game) : pGame(game)
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
		pWindow = new ARenderer();
		if (!pWindow)
		{
			AppTerminate();
		}
		SetVideoParams();
		pWindow->Init(pVideoParams);
	}
	{
		pCallback = new ACallback();
		pCallback->InitKeys();
	}

	pGame->Init();

	CalculateDeltaTime();
	
	Log(ELogType::LT_INFO, "Engine init success\n");
}

void AEngine::Tick()
{
	CalculateDeltaTime();
	pGame->Tick();
	pWindow->Render(pGame);
	pCallback->Tick(DeltaTime);
}

void AEngine::Run()
{
	bool quit = false;

	while(!pWindow->ShouldClose())
	{
		Tick();
	}
}

void AEngine::Finish()
{
	pWindow->finish();
	if(pWindow)
		delete pWindow;
	delete pCallback;
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

ACallback* AEngine::GetCallback()
{
	return pCallback;
}

float AEngine::GetDeltaTime()
{
	return DeltaTime;
}

int AEngine::GetFPS()
{
	return 1 / DeltaTime;
}