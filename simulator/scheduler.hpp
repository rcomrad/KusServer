#pragma once

#include <queue>

#include "event.hpp"

namespace sim
{
class Scheduler
{
public:
    void tick();
    void add(Event event);

private:
    std::priority_queue<Event*> m_events;
};
} // namespace sim
