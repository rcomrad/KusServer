#include "kernel/framework/module/constructor.hpp"
#include "kernel/utility/synchronization/condvar.hpp"

namespace kustest
{

class ModuleConstructor
{
public:
    template <typename T>
    static const core::Module* create(util::Condvar& a_has_started)
    {
        m_ptr = std::make_unique<T>(a_has_started);
        return m_ptr.get();
    }

private:
    inline static std::unique_ptr<core::Module> m_ptr;
    static ModuleConstructor __globalConstructor;

    ModuleConstructor()
    {
        core::ModuleConstructor::getInstance().add("test", construct);
    }

    static core::ModuleConstructor::ModuleType construct()
    {
        return std::move(m_ptr);
    }
};

} // namespace kustest
