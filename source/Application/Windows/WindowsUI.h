#pragma once

#include "../Platform.h"

class WindowsUI : public IPlatform
{
public:
    WindowsUI();
    std::shared_ptr<IDisplay> GetDisplay() override;
    std::queue<Event> GetEvents() override;
private:
    std::shared_ptr<IDisplay> m_pDisplay;
};