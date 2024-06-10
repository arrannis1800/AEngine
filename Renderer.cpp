#include <string>

#include <SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Renderer.h"

#include "Game.h"
#include "MacrosLibrary.h"
#include "Structs/AVideoParams.h"
#include "Structs/ColorRGBA.h"


void AWindow::Init(AVideoParams* VideoParams)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Log(ELogType::ERROR, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		AppTerminate();
	} 

	Window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, VideoParams->Width, VideoParams->Height, VideoParams->Flags); // SDL_WINDOW_SHOWN
	if(Window == NULL)
	{
		Log(ELogType::ERROR, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		AppTerminate();
	} 

	renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

	if( TTF_Init() == -1 )
    {
        Log(ELogType::ERROR, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        AppTerminate();
    } 
	
	font = TTF_OpenFont(VideoParams->FontPath, VideoParams->FontSize); //  24

}

// void draw_rect(int x, int y, int h, int w, uint32_t color)
// {
// 	for (int row = y; row < y+h; ++row)
// 	{
// 		for (int col = x; col < x+w; ++col)
// 		{
// 			if((row >= 0) && (row < frame.Height) && (col >= 0) && (col < frame.Width))
// 			{
// 				frame.screen[col + row*frame.Width] = color;
// 			}
// 		}
// 	}
// };

void AWindow::draw_text(const char* text, uint32_t text_color, bool draw_bg, uint32_t bg_color, int x, int y)
{
	ColorRGBA text_c(text_color);
	ColorRGBA bg_c(bg_color);
	SDL_Surface* SurfaceMessage;
	if(draw_bg)
	{
		SurfaceMessage = TTF_RenderText_LCD(font, text, {text_c.r, text_c.g, text_c.b, text_c.a}, {bg_c.r, bg_c.g, bg_c.b, bg_c.a}); 
	} else
	{
		SurfaceMessage = TTF_RenderText_Solid(font, text, {text_c.r, text_c.g, text_c.b, text_c.a});
	}

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, SurfaceMessage);

	int text_width = SurfaceMessage->w;
	int text_height = SurfaceMessage->h;
	SDL_Rect renderQuad = { x, y, text_width, text_height };
	SDL_RenderCopy(renderer, Message, NULL, &renderQuad);


    SDL_FreeSurface(SurfaceMessage);
	SDL_DestroyTexture(Message);
};

void AWindow::Render(AGame* Game)
{
	SDL_RenderClear(renderer);
	ALevel* CurrentLevel = Game->GetCurrentLevel();
	{
		int w, h;
		SDL_GetWindowSize(Window, &w, &h);
		ColorRGBA c(CurrentLevel->GetLevelSettings()->BackGroundColor);
		SDL_Rect rect = {0,0,w,h};
		SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
		SDL_RenderFillRect(renderer, &rect);
	}

	draw_text("Hello World", 0x000000ff, false, 0xffffffff, 100, 200);


	if(GetEngine())
	{
		draw_text(std::to_string(GetEngine()->GetFPS()).c_str(), 0x000000ff, true, 0xeb4034ff, 20, 30);
	}
	
	draw_text("Hello World with bg", 0x000000ff, true, 0xeb4034ff, 200, 300);

	SDL_RenderPresent(renderer);
}

void AWindow::sdl_finish()
{
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}



