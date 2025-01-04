#include "communication.hpp"

onto::Communication::Communication(const std::string_view& a_name,
                                   Type a_type) noexcept
    : Node(Node::Kind::COMMUNICATION, a_name), m_type(a_type), m_call_count(0)
{
}

onto::Communication::Communication(const std::string_view& a_name,
                                   const std::vector<std::string_view>& a_parts)
    : Node(Node::Kind::COMMUNICATION, a_name)
{
}

std::string
onto::Communication::getNextDataName()
{
    return getName() + "_" + std::to_string(m_call_count);
}

void
onto::Communication::commitNextDataName()
{
    m_call_count++;
}
