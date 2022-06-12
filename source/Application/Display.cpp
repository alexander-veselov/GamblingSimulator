#include "Display.h"

#include <SDL.h>
#include <SDL_ttf.h>

namespace
{
const size_t g_symbolSize = 75;

void drawTextAt(SDL_Renderer* renderer, std::string text, size_t x0, size_t y0)
{
	static TTF_Font* font = TTF_OpenFont("resources/font.ttf", 25);
	
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), {0, 0, 0});
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect messageRect;
	messageRect.x = x0 + (g_symbolSize - surfaceMessage->w) / 2;
	messageRect.y = y0 + (g_symbolSize - surfaceMessage->h) / 2;
	messageRect.w = surfaceMessage->w;
	messageRect.h = surfaceMessage->h;

	SDL_RenderCopy(renderer, message, nullptr, &messageRect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}
}

void Display(DisplayData displayData)
{
	for (size_t i = 0; i < displayData.board.size(); ++i)
	{
		for (size_t j = 0; j < displayData.board[i].size(); ++j)
		{
			const std::string symbol = displayData.board[i][j].GetName();
			drawTextAt(displayData.renderer, symbol, j * g_symbolSize, i * g_symbolSize);
		}
	}
}