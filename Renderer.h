#include <stdio.h>
#include <vector>

#include <SDL.h>
#include <SDL2/SDL_ttf.h>

#include "MacrosLibrary.h"
#include "World.h"
#include "AVideoParams.h"
#include "LevelSettings.h"

struct ColorRGBA
{
	ColorRGBA() = default;

	ColorRGBA(uint32_t color)
	{
		r = (color >> (8*3)) & 0xff;
		g = (color >> (8*2)) & 0xff;
		b = (color >> (8*1)) & 0xff;
		a = (color >> (8*0)) & 0xff;
	}

	uint32_t toUInt32()
	{
		return (r << 24) | (g << 16) | (b << 8) | a;
	};

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

struct Frame
{
	int Height = 0;
	int Width = 0;
	std::vector<uint32_t> screen;
};

class AWindow
{
public:
	void Init(AVideoParams* VideoParams)
	{
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			AppTerminate();
		} 

		Window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, VideoParams->Width, VideoParams->Height, VideoParams->Flags); // SDL_WINDOW_SHOWN
		if(Window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			AppTerminate();
		} 

		renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

		if( TTF_Init() == -1 )
	    {
	        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
	        AppTerminate();
	    } 
		
		font = TTF_OpenFont(VideoParams->FontPath, VideoParams->FontSize); //  24

	}

	void color_pixel(uint32_t color, int col, int row)
	{
		ColorRGBA c(color);
		SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
		SDL_RenderDrawPoint(renderer, col, row);
	}

	// void fill_screen(uint32_t color)
	// {
	// 	frame.screen = std::vector<uint32_t>(frame.Height*frame.Width, color);
	// };

	void draw_rect(int x, int y, int h, int w, uint32_t color)
	{
		for (int row = y; row < y+h; ++row)
		{
			for (int col = x; col < x+w; ++col)
			{
				if((row >= 0) && (row < frame.Height) && (col >= 0) && (col < frame.Width))
				{
					frame.screen[col + row*frame.Width] = color;
				}
			}
		}
	};

	void draw_text(const char* text, uint32_t text_color, bool draw_bg, uint32_t bg_color, int x, int y)
	{
		ColorRGBA text_c(text_color);
		ColorRGBA bg_c(bg_color);
		if(!draw_bg)
			bg_c.a = 0;
		SDL_Surface* surfaceMessage  = TTF_RenderText_LCD(font, text, {text_c.a, text_c.r, text_c.g, text_c.b}, {bg_c.a, bg_c.r, bg_c.g, bg_c.b}); 

		for (int row = 0; row < surfaceMessage->h; ++row)
	    {
	        for (int col = 0; col < surfaceMessage->w; ++col)
	        {
	            int frameX = x + col;
	            int frameY = y + row;

	            if (frameX >= 0 && frameX < frame.Width && frameY >= 0 && frameY < frame.Height)
	            {
	            	uint32_t pixel = ((uint32_t *)surfaceMessage->pixels)[ ( row * surfaceMessage->w ) + col ];
	            	ColorRGBA c;
	            	SDL_GetRGBA(pixel, surfaceMessage->format, &c.r, &c.g, &c.b, &c.a);

	                // printf("%zx\n", c.toUInt32());
	                // if((pixelColor & 0xff) != 0x00)
	                	frame.screen[frameX + frameY * frame.Width] = c.toUInt32();
	            }
	        }
	    }


	    SDL_FreeSurface(surfaceMessage);
	};

	bool update_frame();

	void scale_frame();

	void Render(AWorld* World)
	{
		SDL_RenderClear(renderer);
		ALevelSettings* ls = World->GetCurrentLevel()->GetLevelSettings();
		int w, h;
		SDL_GetWindowSize(Window, &w, &h);

	    for (int row = 0; row < h; ++row)
	    {
	    	for (int col = 0; col < w; ++col)
	    	{
	    		ColorRGBA c(ls->BackGroundColor);
				SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
				SDL_RenderDrawPoint(renderer, col, row);
	    	}
	    }
	    SDL_SetRenderDrawColor(renderer, 0,0,0,255);

		SDL_RenderPresent(renderer);
	}

	bool sdl_draw_screen()
	{
		bool success = true;


		if (renderer == nullptr)
	    {
	        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
	        success = false;
	        return success;
	    }

	    SDL_RenderClear(renderer);

	    for (int row = 0; row < frame.Height; ++row)
	    {
	    	for (int col = 0; col < frame.Width; ++col)
	    	{
	    		color_pixel(frame.screen[col + row*frame.Width], col, row);
	    	}
	    }
	    SDL_SetRenderDrawColor(renderer, 0,0,0,255);

		SDL_RenderPresent(renderer);

		SDL_Delay(100);

		return success;
	}

	void sdl_finish()
	{
	    SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(Window);
		SDL_Quit();
	}

private:
	SDL_Window* Window;
	SDL_Renderer* renderer;
	TTF_Font* font;
public:
	Frame frame;

};


