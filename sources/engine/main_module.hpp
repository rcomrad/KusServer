#include "graphics/heart.hpp"
#include "kernel/framework/module/include_me.hpp"
#include "kernel/utility/type/declaration/lifecycle_manager.hpp"

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
    util::LifecycleManager<Heart> m_graphics;
};

} // namespace engine
