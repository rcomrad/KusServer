#include "kernel/framework/module/include_me.hpp"

namespace engine
{

class MainModule : public core::ThreadModule
{
public:
    MainModule();

protected:
    void threadInitialize() override;
    bool threadLoopBody() override;
    void threadTerminate() override;
};

} // namespace engine
