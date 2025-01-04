#pragma once

#include <string>
#include <string_view>

#include "node.hpp"

namespace onto
{

class Communication : public Node
{
public:
    enum class Type
    {
        INPUT,
        OUTPUT
    };
    Communication(const std::string_view& a_name, Type a_type) noexcept;
    Communication(const std::string_view& a_name,
                  const std::vector<std::string_view>& a_parts);

    std::string getNextDataName();
    void commitNextDataName();

private:
    Type m_type;
    int m_call_count;
};

} // namespace onto
