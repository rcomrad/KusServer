#include "objects.hpp"

game::obj::Object_CD::Object_CD(ObjectInfo const& a_obj_info) noexcept
    : BaseObject(getType(), a_obj_info.level),
      Coordinatable(a_obj_info),
      Drawable(a_obj_info)
{
}

game::obj::Object_CDH::Object_CDH(ObjectInfo const& a_obj_info) noexcept
    : BaseObject(getType(), a_obj_info.level),
      Coordinatable(a_obj_info),
      Drawable(a_obj_info),
      Hitable(a_obj_info)
{
}

game::obj::Object_CDT::Object_CDT(ObjectInfo const& a_obj_info) noexcept
    : BaseObject(getType(), a_obj_info.level),
      Coordinatable(a_obj_info),
      Drawable(a_obj_info),
      Textable(a_obj_info)
{
}

game::obj::Object_CDHT::Object_CDHT(ObjectInfo const& a_obj_info) noexcept
    : BaseObject(getType(), a_obj_info.level),
      Coordinatable(a_obj_info),
      Drawable(a_obj_info),
      Hitable(a_obj_info),
      Textable(a_obj_info)
{
}

game::obj::Object_CT::Object_CT(ObjectInfo const& a_obj_info) noexcept
    : BaseObject(getType(), a_obj_info.level),
      Coordinatable(a_obj_info),
      Textable(a_obj_info)
{
}
