#include "Application.h"

namespace
{
	Slot GetSlot()
	{
		static Lines lines;
		static Symbols symbols;

		symbols.AddSymbol(0.30, Symbol(0, "O", { 1 }));
		symbols.AddSymbol(0.25, Symbol(1, "J", { 2 }));
		symbols.AddSymbol(0.17, Symbol(2, "Q", { 4 }));
		symbols.AddSymbol(0.13, Symbol(3, "K", { 8 }));
		symbols.AddSymbol(0.10, Symbol(4, "A", { 16 }));
		symbols.AddSymbol(0.05, Symbol(4, "W", { 32 }));

		static Slot slot(3, 3, symbols, lines);

		return slot;
	}
}

Application::Application(std::shared_ptr<IDisplay> display)
	: m_slot(GetSlot()), m_display(display)
{}

void Application::Process(Event event)
{
	switch (event)
	{
	case Event::UPDATE:
		m_display->Display(DisplayData(m_lastWin, m_wonTotal, m_spentTotal, m_slot.GetLastBoard()));
		break;
	case Event::KEY_PRESSED:
		OnKeyPressed();
		break;
	case Event::IDLE:
		break;
	}
}

void Application::OnKeyPressed()
{
	m_lastWin = m_slot.MakeSpin();
	m_wonTotal += m_lastWin;
	++m_spentTotal;
}