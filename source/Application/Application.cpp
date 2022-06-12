#include "Application.h"

#include <iostream>

namespace
{
	Slot GetSlot()
	{
		static Lines lines;
		static Symbols symbols;

		symbols.AddSymbol(0.30, Symbol(0, "10", { 2 }));
		symbols.AddSymbol(0.25, Symbol(1, "J", { 3 }));
		symbols.AddSymbol(0.20, Symbol(2, "Q", { 4 }));
		symbols.AddSymbol(0.13, Symbol(3, "K", { 8 }));
		symbols.AddSymbol(0.12, Symbol(4, "A", { 16 }));

		static Slot slot(3, 3, symbols, lines);

		return slot;
	}
}

Application::Application()
	: m_slot(GetSlot())
{
	m_slot.GenerateRandomBoard();
}

void Application::SetRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void Application::Handle(Event event)
{
	switch (event)
	{
	case Event::UPDATE:
	case Event::IDLE:
		Display(DisplayData(m_lastWin, m_wonTotal, m_spentTotal, m_slot.GetBoard(), renderer));
		break;
	case Event::KEY_PRESSED:
		OnKeyPressed();
		break;
	
		break;
	}
}

void Application::OnKeyPressed()
{
	m_slot.GenerateRandomBoard();
	m_lastWin = m_slot.MakeSpin();
	m_wonTotal += m_lastWin;
	++m_spentTotal;

	std::cout << "Last win: " << m_lastWin << std::endl;
	std::cout << "Total win: " << m_wonTotal << std::endl;
	std::cout << "Spent: " << m_spentTotal << std::endl;
}