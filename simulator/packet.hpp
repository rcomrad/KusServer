#pragma once

#include <queue>
#include <unordered_map>

#include "flow.hpp"

class Node;

namespace sim
{

struct Packet
{
    Node* src;
    Node* dest;
    Node* next; // for next hop
    Flow* flow;
};

} // namespace sim
