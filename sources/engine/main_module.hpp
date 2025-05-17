#include "kernel/framework/module/thread_module.hpp"

namespace engine
{

class MainModule : public core::ThreadModule
{
    void threadInitialize() override;
    bool threadLoopBody() override;
    void threadTerminate() override;
};

} // namespace engine
