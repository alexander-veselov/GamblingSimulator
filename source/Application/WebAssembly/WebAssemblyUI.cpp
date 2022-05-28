#include "WebAssemblyUI.h"

#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#include <iostream>

using namespace emscripten;

namespace
{

bool makeSpin = false;

void spin()
{
	makeSpin = true;
}

EMSCRIPTEN_BINDINGS(my_module) {
	function("spin", &spin);
}

class WebAssemblyDisplay : public IDisplay
{
	void Display(DisplayData displayData) const override
	{
		std::cout << "Board:" << std::endl;
		for (const Line& line : displayData.board)
		{
			for (const Symbol& symbol : line)
			{
				std::cout << symbol.GetName() << " ";
			}
			std::cout << std::endl;
		}

		std::cout << "Last win: " << displayData.lastWin << std::endl;
		std::cout << "Spent total: " << displayData.spentTotal << std::endl;
		std::cout << "Won total: " << displayData.wonTotal << std::endl;
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