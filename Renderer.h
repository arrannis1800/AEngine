#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Game.h"
#include "Structs/AVideoParams.h"

class AWindow
{
public:
	void Init(AVideoParams* VideoParams);

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

	void draw_text(const char* text, uint32_t text_color, bool draw_bg, uint32_t bg_color, int x, int y);

	void Render(AGame* Game);

	void sdl_finish();

private:
	SDL_Window* Window;
	SDL_Renderer* renderer;
	TTF_Font* font;

};


#endif