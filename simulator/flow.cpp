#include "flow.hpp"

void
sim::Flow::start()
{
    m_scheduler.add(GeneratePacketEvent());
}

bool
sim::Flow::try_generate()
{
    bool result = false;
    if (m_cur_window < m_max_window)
    {
        m_cur_window++;
        result = true;
    }
    return result;
}

void
sim::Flow::recive_ack()
{
    m_scheduler.add(GeneratePacketEvent());
}
