#include "mesh_combiner.hpp"

#include <iostream>

#include "engine/render_manager/model/model.hpp"

namespace kusengine
{
namespace render
{
RangeInfo::RangeInfo()
    : vertex_offset(0),
      index_count(0),
      first_index(0),
      instance_count(0),
      first_instance(0)
{
}
}; // namespace render
}; // namespace kusengine
