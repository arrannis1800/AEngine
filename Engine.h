#include <chrono>

#include "Renderer.h"
#include "World.h"
#include "MacrosLibrary.h"

#include <SDL.h>

class AEngine
{
private:
	friend SDL_main(int, char**);
	AEngine(AWorld* World) : World(World)
	{
		VideoParams = new AVideoParams;
	};
public:

	void Init()
	{
		World->Init();

		Window = new AWindow();
		if(!Window)
		{
			AppTerminate();
		}

		VideoParams->Width = 700;
		VideoParams->Height = 700;
		VideoParams->Flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE; 
		VideoParams->FontSize = 24;

		Window->Init(VideoParams);
		Log(ELogType::INFO, "Engine init success\n");
	};

	void Tick()
	{
		CalculateDeltaTime();
		// TODO: GameMode->Tick
		World->Tick();
		Window->Render(World);
		// SDL_Delay(1000);
	}

	void Run()
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
	};

	void Finish()
	{
		Window->sdl_finish();
		if(Window)
			delete Window;
		delete VideoParams;
	};

	void Start()
	{
		Init();

		Run();

		Finish();
	};

	void CalculateDeltaTime()
	{
		std::chrono::time_point<std::chrono::steady_clock> Now = std::chrono::steady_clock::now();
		DeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(Now - LastTime).count() / 1000.0f / 1000.0f;
		LastTime = Now;
	}

	float GetDeltaTime()
	{
		return DeltaTime;
	}

private:
	AWorld* World = nullptr;
	AWindow* Window = nullptr;
	AVideoParams* VideoParams;
	float DeltaTime;
	std::chrono::time_point<std::chrono::steady_clock> LastTime;
};