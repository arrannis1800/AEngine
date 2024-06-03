
#include "Engine.h"
#include "MacrosLibrary.h"
#include "Config.h"

AEngine* gEngineInstance = nullptr;

AEngine::AEngine(AWorld* World) : World(World)
{
	gEngineInstance = this;
};

void AEngine::SetVideoParams()
{
	VideoParams = &config::VideoParams;
	Log(ELogType::INFO, "Video Prarms set\n\tWidth = %d\n\tHeight = %d\n\tFlags = %zu\n", 
		VideoParams->Width, VideoParams->Height, VideoParams->Flags);
}

void AEngine::Init()
{
	World->Init();

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
	World->Tick();
	Window->Render(World);
}

void AEngine::Run()
{
bool quit = false;
SDL_Event e;

while(!quit)
{
	while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            quit = true;
    }
	Tick();
}
}

void AEngine::Finish()
{
	Window->sdl_finish();
	if(Window)
		delete Window;
	delete VideoParams;
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