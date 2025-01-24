#pragma once

namespace sim
{

class Scheduler;

class Flow
{
public:
    void start();
    bool try_generate();
    void recive_ack();

private:
    int m_max_window;
    int m_cur_window;
    Scheduler m_scheduler;
};

} // namespace sim
