#include "kernel/framework/module/include_me.hpp"
#include "kernel/utility/type/declaration/lifecycle_manager.hpp"

#include "window.hpp"

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

private:
    util::LifecycleManager<Window> m_window;
};

} // namespace engine
