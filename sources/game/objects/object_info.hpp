#pragma once

#include <optional>
#include <string>
#include <unordered_set>

#include "gpu/utils/typedef.hpp"

namespace game::obj
{

struct ObjectInfo
{
    std::optional<int> level;
    std::unordered_set<std::string> flags;
    std::unordered_set<std::string> type;

    std::optional<gpu::type::NDC> ndc;
    std::optional<gpu::type::Coordinates> coordinates;

    std::optional<std::string> texture;
    std::optional<std::string> sprite_view;

    std::optional<std::string> text;
    std::optional<std::string> font;
    std::optional<std::string> font_id;
};

} // namespace game::obj
