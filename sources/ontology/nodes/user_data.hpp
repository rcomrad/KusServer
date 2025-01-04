#pragma once

#include <string_view>

#include "communication.hpp"
#include "node.hpp"

namespace onto
{

class UserData : public Node
{
public:
    UserData(Communication& a_comm) noexcept;
    UserData(const std::string_view& a_name,
             const std::vector<std::string_view>& a_parts);

    void output(Node& a_data);
};

} // namespace onto
