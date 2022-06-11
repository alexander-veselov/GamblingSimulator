#pragma once

#include "../Platform.h"

class WebAssemblyUI : public IPlatform
{
public:
    WebAssemblyUI();
    std::shared_ptr<IDisplay> GetDisplay() override;
    std::queue<Event> GetEvents() override;
private:
    std::shared_ptr<IDisplay> m_pDisplay;
};