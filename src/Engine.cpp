#include "Engine.h"
#include "MacrosLibrary.h"
#include "Config.h"

AEngine* gEngineInstance = nullptr;

AEngine::AEngine(AGame* Game) : Game(Game)
{
	gEngineInstance = this;
};

void AEngine::SetVideoParams()
{
	VideoParams = &config::VideoParams;
	Log(ELogType::INFO, "Video Prarms set\n\tWidth = %d\n\tHeight = %d\n", VideoParams->Width, VideoParams->Height);
}

void AEngine::Init()
{
	Game->Init();

	SetVideoParams();

	Window = new AWindow();
	if(!Window)
	{
		AppTerminate();
	}
	
	Window->Init(VideoParams);
	CalculateDeltaTime();
	Log(ELogType::INFO, "Engine init success\n");
}

void AEngine::Tick()
{
	CalculateDeltaTime();
	Game->Tick();
	Window->Render(Game);
}

void AEngine::Run()
{
	bool quit = false;

	while(!Window->ShouldClose())
	{
		Tick();
	}
}

void AEngine::Finish()
{
	Window->finish();
	if(Window)
		delete Window;
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