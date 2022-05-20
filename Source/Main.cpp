//#include <emscripten.h>

#include "Core/Slot.h"

#include <iostream>
#include <conio.h>

int main()
{
	Symbols symbols;
	symbols.AddSymbol(0.30, Symbol(0, "O", { 1 }));
	symbols.AddSymbol(0.25, Symbol(1, "J", { 2 }));
	symbols.AddSymbol(0.17, Symbol(2, "Q", { 4 }));
	symbols.AddSymbol(0.13, Symbol(3, "K", { 8 }));
	symbols.AddSymbol(0.10, Symbol(4, "A", { 16 }));
	symbols.AddSymbol(0.05, Symbol(4, "W", { 32 }));

	Lines lines;

	Slot slot(3, 3, symbols, lines);

	size_t spent = 0;
	size_t won = 0;

	// Board:
	// K O O
	// Q Q W
	// W A A
	// Win : 32

	while (true)
	{
		system("cls");
		size_t win = slot.MakeSpin();
		Board board = slot.GetLastBoard();

		std::cout << "Board:" << std::endl;
		for (const Line& line : board)
		{
			for (const Symbol& symbol : line)
			{
				std::cout << symbol.GetName() << " ";
			}
			std::cout << std::endl;
		}

		++spent;
		won += win;
		std::cout << "Win:" << win << std::endl;
		std::cout << "Spent:" << spent << std::endl;
		std::cout << "Won:" << won << std::endl;

		getch();
	}

	return 0;
}