#include "WindowsUI.h"

#include <iostream>
#include <Windows.h>

namespace
{
void ConsoleGoto(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}
}

void WindowsUI::Display(DisplayData displayData) const
{
	ConsoleGoto(0, 0);

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