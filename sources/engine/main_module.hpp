#include "kernel/framework/module/include_me.hpp"

namespace engine
{

class MainModule : public core::ThreadModule
{
    void threadInitialize() override;
    bool threadLoopBody() override;
    void threadTerminate() override;

    static core::ModuleRegister<MainModule> reg;
};

template <typename T>
core::ModuleRegister<MainModule> S<T>::something_relevant = 1.5;

} // namespace engine
