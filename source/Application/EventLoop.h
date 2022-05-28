#pragma once

#include "ISubscriable.h"

#include <memory>
#include <vector>

class EventLoop
{
public:
    void Subscribe(std::shared_ptr<ISubscriable> pSubscriable);
    int Run() const;
private:
    std::vector<Event> GetEvents() const; // TODO: Is that correct?
private:
    std::vector<std::shared_ptr<ISubscriable>> m_subcribed;
};
