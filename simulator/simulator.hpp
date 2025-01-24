#pragma once

#include <string>
#include <unordered_map>

#include "node.hpp"
#include "scheduler.hpp"

namespace sim
{
class Simulator
{
public:
    void createNode(std::string a_name, size_t a_buffer_size);
    void createLink(std::string a_node1, std::string a_node2, size_t a_delay);

    void start();

private:
    Scheduler m_scheduler;
    std::unordered_map<std::string, Node*> m_graph;
    std::vector<Flow> m_flows;
};
} // namespace sim
