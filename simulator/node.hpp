#pragma once

#include <queue>
#include <unordered_map>

#include "packet.hpp"
#include "scheduler.hpp"

namespace sim
{

class Node
{
public:
    void connect(Node* a_node, int a_buffer_size);

    void receive(Packet a_packet);
    virtual void process(); // override for server/receiver
    void send(Node* a_node);

    void generate_packet(Node* a_dest, Flow* flow);

    // bfs (use m_neighbors)
    // called from above for all nodes separatly / one large bfs
    // its result used by get_next_hop func
    void recalculate_paths();

private:
    int m_buffer_size;
    std::queue<Packet> m_buffer;
    Scheduler m_scheduler;

    // m_routing_table by recalculate_paths() for get_next_hop()

    struct LinkBuffer
    {
        int size;
        std::queue<Packet> m_buffer;
    };
    std::unordered_map<Node*, LinkBuffer> m_neighbors;

    // if we have non-zero receiving buffer we schedule packet processing:
    // 1) after new packet was received
    // or
    // 2) packet was processed
    //    (schedule processing of next already received packet)
    void plan_process();
    Node* get_next_hop(Node*);
};

} // namespace sim
