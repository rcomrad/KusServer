#include "scheduler.hpp"

#include "node.hpp"

void
sim::Scheduler::tick()
{
    auto event = m_events.top();
    m_events.pop();
    event();
}
