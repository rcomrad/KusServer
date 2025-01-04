#pragma once

#include <string>

#include "web.hpp"

namespace onto
{

class WebFactory
{
public:
    WebFactory() = delete;

    static Web fromFile(const std::string& a_filename) noexcept;
};

} // namespace onto
