#pragma once

#include "base_object.hpp"
#include "drawable.hpp"
#include "hitable.hpp"
#include "object_info.hpp"
#include "object_type.hpp"
#include "textable.hpp"

namespace game::obj
{

struct ObjectInfo;

class Object_CD : public BaseObject, public Drawable
{
public:
    Object_CD(ObjectInfo const& a_obj_info) noexcept;

    static constexpr int getType()
    {
        return static_cast<int>(Type::COORDINATABLE) |
               static_cast<int>(Type::DRAWABLE);
    }
};

class Object_CDH : public BaseObject, public Drawable, public Hitable
{
public:
    Object_CDH(ObjectInfo const& a_obj_info) noexcept;

    static constexpr int getType()
    {
        return static_cast<int>(Type::COORDINATABLE) |
               static_cast<int>(Type::DRAWABLE) |
               static_cast<int>(Type::HITABLE);
    }
};

class Object_CDT : public BaseObject, public Drawable, public Textable
{
public:
    Object_CDT(ObjectInfo const& a_obj_info) noexcept;

    static constexpr int getType()
    {
        return static_cast<int>(Type::COORDINATABLE) |
               static_cast<int>(Type::DRAWABLE) |
               static_cast<int>(Type::TEXTABLE);
    }
};

class Object_CDHT : public BaseObject,
                    public Drawable,
                    public Hitable,
                    public Textable
{
public:
    Object_CDHT(ObjectInfo const& a_obj_info) noexcept;

    static constexpr int getType()
    {
        return static_cast<int>(Type::COORDINATABLE) |
               static_cast<int>(Type::DRAWABLE) |
               static_cast<int>(Type::HITABLE) |
               static_cast<int>(Type::TEXTABLE);
    }
};

class Object_CT : public BaseObject, public Textable
{
public:
    Object_CT(ObjectInfo const& a_obj_info) noexcept;

    static constexpr int getType()
    {
        return static_cast<int>(Type::COORDINATABLE) |
               static_cast<int>(Type::TEXTABLE);
    }
};

} // namespace game::obj
