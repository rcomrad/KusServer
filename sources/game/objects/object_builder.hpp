#pragma once

#include <memory>

namespace game::obj
{

class BaseObject;
struct ObjectInfo;

std::unique_ptr<BaseObject>
createObject(const ObjectInfo& a_obj_info);

} // namespace game::obj
