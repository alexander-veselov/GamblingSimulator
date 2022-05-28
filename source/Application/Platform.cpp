#include "Platform.h"

#include "Windows/WindowsUI.h"

Platform::Platform()
{
    m_pDisplay.reset(new WindowsUI());
}

std::shared_ptr<IDisplay> Platform::GetDisplay() const
{
    return m_pDisplay;
}