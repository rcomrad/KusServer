#include "deleted.hpp"

onto::Deleted::Deleted(const std::string_view& a_name)
    : Node(Node::Kind::DELETED, a_name)
{
}

onto::Deleted::Deleted(const std::string_view& a_name,
                       const std::vector<std::string_view>& a_parts)
    : Node(Node::Kind::DELETED, a_name)
{
}
