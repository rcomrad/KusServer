#include "simulator.hpp"

void
sim::Simulator::createNode(std::string a_name, size_t a_buffer_size)
{
    if (!m_graph.count(a_name))
    {
        m_graph.emplace(a_name, a_buffer_size);
    }
    else
    {
        throw;
    }
}

void
sim::Simulator::start()
{
    for (auto& i : m_flows) i.start();
}
