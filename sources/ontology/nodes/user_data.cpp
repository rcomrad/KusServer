#include "user_data.hpp"

onto::UserData::UserData(Communication& a_comm) noexcept
    : Node(Node::Kind::USER_DATA, a_comm.getNextDataName())
{
    a_comm.commitNextDataName();
    addNeighbor(a_comm, Relation::FROM);
}

onto::UserData::UserData(const std::string_view& a_name,
                         const std::vector<std::string_view>& a_parts)
    : Node(Node::Kind::COMMUNICATION, a_name)
{
}

void
onto::UserData::output(Node& a_data)
{
    addNeighbor(a_data, Relation::STORES);
}
