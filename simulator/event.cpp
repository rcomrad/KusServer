#include "event.hpp"

#include "node.hpp"
#include "scheduler.hpp"

void
sim::ReciveEvent::operator()()
{
    packet.node->receive(packet);
}

void
sim::ProcessEvent::operator()()
{
    node->process();
}

void
sim::SendEvent::operator()()
{
    from->send(next);
}

void
sim::GeneratePacketEvent::operator()()
{
    node->generate_packet(dest);
    m_scheduler.add(SendEvent);

    if (flow->try_generate())
    {
        m_scheduler.add(GeneratePacketEvent);
    }
}
