#include "node.hpp"

void
sim::Node::connect(Node* a_node, int a_buffer_size)
{
    if (!m_neighbors.count(a_node))
    {
        m_neighbors.emplace(a_node, a_buffer_size);
    }
    else
    {
        throw;
    }
}

void
sim::Node::receive(Packet a_packet)
{
    if (m_buffer.size() < m_buffer_size)
    {
        m_buffer.emplace(a_packet);
        if (m_buffer.size() == 1)
        {
            plan_process(); // schedule next packet processing on this node
        }
    }
}

void
sim::Node::process()
{
    auto packet = m_buffer.front();
    m_buffer.pop();
    plan_process(); // schedule next packet processing on this node

    // overrided server/receiver logic

    auto next = get_next_hop(packet.dest);
    m_scheduler.add(SendEvent(0, this, next));
}

void
sim::Node::send(Node* a_node)
{
    auto it         = m_neighbors.find(a_node); // check
    auto& link_buff = it->second;

    auto packet = link_buff.front();
    link_buff.pop();
    m_scheduler.add(ReciveEvent(0, a_node));
}

void
sim::Node::plan_process()
{
    if (m_buffer.size() > 1)
    {
        m_scheduler.add(ProcessEvent(0, this));
    }
}
