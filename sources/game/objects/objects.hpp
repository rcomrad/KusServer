#pragma once

#include "base_object.hpp"
#include "drawable.hpp"
#include "hitable.hpp"
#include "object_info.hpp"
#include "textable.hpp"

namespace game::obj
{

class Object_CD : public BaseObject, public Coordinatable, public Drawable
{
    Object_CDH(const int a_level,
               Coordinatable&& a_coord,
               Drawable&& a_draw) noexcept;

    constexpr static int getType();
};

class Object_CDH : public BaseObject,
                   public Coordinatable,
                   public Drawable,
                   public Hitable
{
    Object_CDH(const int a_level,
               Coordinatable&& a_coord,
               Drawable&& a_draw,
               Hitable&& a_hit) noexcept;

    constexpr static int getType();
};

class Object_CDT : public BaseObject,
                   public Coordinatable,
                   public Drawable,
                   public Textable
{
    Object_CDT(const int a_level,
               Coordinatable&& a_coord,
               Drawable&& a_draw,
               Textable&& a_text) noexcept;

    constexpr static int getType();
};

class Object_CDHT : public BaseObject,
                    public Coordinatable,
                    public Drawable,
                    public Hitable,
                    public Textable
{
    Object_CDHT(const int a_level,
                Coordinatable&& a_coord,
                Drawable&& a_draw,
                Hitable&& a_hit,
                Textable&& a_text) noexcept;

    constexpr static int getType();
};

class Object_CT : public BaseObject, public Coordinatable, public Textable
{
    Object_CT(const int a_level,
              Coordinatable&& a_coord,
              Textable&& a_text) noexcept;

    constexpr static int getType();
};

} // namespace game::obj
