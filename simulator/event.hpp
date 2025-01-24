#pragma once

#include <any>
#include <queue>

namespace sim
{

class Packet;
class Scheduler;

struct Event
{
    int time;
    Scheduler m_scheduler;
    virtual void operator()() = 0;
};

struct ReciveEvent
{
    Node* node;
    Packet packet;

    virtual void operator()() final;
};

struct ProcessEvent
{
    Node* node;

    virtual void operator()() final;
};

struct SendEvent
{
    Node* from;
    Node* next;

    virtual void operator()() final;
};

struct GeneratePacketEvent
{
    Node* src;
    Node* dest;
    Flow* flow;

    virtual void operator()() final;
};


// LinkDownEvent 
// DelayAddEvent
// NetworkReconfigurateEvent

} // namespace sim
