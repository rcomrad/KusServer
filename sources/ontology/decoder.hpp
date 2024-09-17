#pragma once

#include <string>
#include <unordered_set>

#include "command.hpp"
#include "web.hpp"

namespace onto
{

class Decoder
{
public:
    // void process(const std::string& a_str) noexcept;
    static std::string process(Web& a_web,
                               const std::string& a_data) noexcept;

private:
    static void processWord(Web& a_web,
                            Command& a_command,
                            const std::string& a_word) noexcept;
    // std::string m_command_buffer;
};

} // namespace onto
