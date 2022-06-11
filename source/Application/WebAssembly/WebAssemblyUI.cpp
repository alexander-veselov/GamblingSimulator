#include "WebAssemblyUI.h"

#include <emscripten.h>
#include <emscripten/bind.h>

#include <iostream>


#include <SDL/SDL_ttf.h>

namespace
{

bool makeSpin = false;

void spin()
{
	makeSpin = true;
}

EMSCRIPTEN_BINDINGS(my_module) {
	emscripten::function("spin", &spin);
}

void draw_text_at(SDL_Renderer* scr, const char* msg, int x0, int y0)
{
	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}

	TTF_Font* font = TTF_OpenFont("resources/font.ttf", 72);
	SDL_Color White = { 0, 0, 0 };

	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Solid(font, msg, White);

	// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(scr, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x0 + (75 - surfaceMessage->w) / 2;  //controls the rect's x coordinate 
	Message_rect.y = y0 + (75 - surfaceMessage->h) / 2; // controls the rect's y coordinte
	Message_rect.w = surfaceMessage->w; // controls the width of the rect
	Message_rect.h = surfaceMessage->h; // controls the height of the rect

	// (0,0) is on the top left of the window/screen,
	// think a rect as the text's box,
	// that way it would be very simple to understand

	// Now since it's a texture, you have to put RenderCopy
	// in your game loop area, the area where the whole code executes

	// you put the renderer's name first, the Message,
	// the crop size (you can ignore this if you don't want
	// to dabble with cropping), and the rect which is the size
	// and coordinate of your texture
	SDL_RenderCopy(scr, Message, NULL, &Message_rect);

	// Don't forget to free your surface and texture
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

class WebAssemblyDisplay : public IDisplay
{
	void Display(DisplayData displayData) const override
	{
		int i = 0;
		for (const Line& line : displayData.board)
		{

			int j = 0;
			for (const Symbol& symbol : line)
			{

				draw_text_at(displayData.scr, symbol.GetName().c_str(), i * 75, j * 75);
				++j;
			}
			++i;
		}

	}
};

}

WebAssemblyUI::WebAssemblyUI()
{
	m_pDisplay.reset(new WebAssemblyDisplay());
}

std::shared_ptr<IDisplay> WebAssemblyUI::GetDisplay()
{
	return m_pDisplay;
}

std::queue<Event> WebAssemblyUI::GetEvents()
{
	std::queue<Event> eventQueue;
	if (makeSpin)
	{
		eventQueue.push(Event::KEY_PRESSED);
		eventQueue.push(Event::UPDATE);
		makeSpin = false;
	}
	return eventQueue;
}