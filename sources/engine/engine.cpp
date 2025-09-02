#include "engine.hpp"

SINGLETON_DEFINITOR(kusengine, Engine)

namespace kusengine
{

Engine::Engine() noexcept : core::Module("engine")
{
}

void
Engine::run() noexcept
{
    if (!m_app.initApp())
    {
        return;
    }

    while (true)
    {
        if (!loopBody())
        {
            break;
        }
    }
}

bool
Engine::loopBody() noexcept
{
    return m_app.loopBody();
}

}; // namespace kusengine
