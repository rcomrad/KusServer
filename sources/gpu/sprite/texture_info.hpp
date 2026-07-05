#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "gpu/utils/typedef.hpp"

namespace gpu::sprite
{

struct TextureInfo
{
    type::Dimensions dimensions     = {1, 1};
    type::Coordinates hitbox_offset = {0, 0};
    std::unordered_map<std::string, std::vector<int>> animation;
};

} // namespace gpu::sprite
