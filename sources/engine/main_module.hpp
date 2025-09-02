#include "kernel/framework/module/include_me.hpp"

#include "app.hpp"
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

    kusengine::App m_app;

    bool was_init = false;
};

} // namespace engine
