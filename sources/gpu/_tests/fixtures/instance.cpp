#include "instance.hpp"

namespace kustest
{

gpu::hard::Instance&
InstanceFixture::instance()
{
    return m_instance;
}

} // namespace kustest
