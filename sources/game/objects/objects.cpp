#include "objects.hpp"

game::obj::Object_CD::Object_CD(const int a_level,
                                Coordinatable&& a_coord,
                                Drawable&& a_draw) noexcept
    : BaseObject(getType(), a_level),
      Coordinatable(std::move(a_coord)),
      Drawable(std::move(a_draw))
{
}

game::obj::Object_CDH::Object_CDH(const int a_level,
                                  Coordinatable&& a_coord,
                                  Drawable&& a_draw,
                                  Hitable&& a_hit) noexcept
    : BaseObject(getType(), a_level),
      Coordinatable(std::move(a_coord)),
      Drawable(std::move(a_draw)),
      Hitable(std::move(a_hit))
{
}

game::obj::Object_CDT::Object_CDT(const int a_level,
                                  Coordinatable&& a_coord,
                                  Drawable&& a_draw,
                                  Textable&& a_text) noexcept
    : BaseObject(getType(), a_level),
      Coordinatable(std::move(a_coord)),
      Drawable(std::move(a_draw)),
      Textable(std::move(a_text))
{
}

game::obj::Object_CDHT::Object_CDHT(const int a_level,
                                    Coordinatable&& a_coord,
                                    Drawable&& a_draw,
                                    Hitable&& a_hit,
                                    Textable&& a_text) noexcept
    : BaseObject(getType(), a_level),
      Coordinatable(std::move(a_coord)),
      Drawable(std::move(a_draw)),
      Hitable(std::move(a_hit)),
      Textable(std::move(a_text))
{
}

game::obj::Object_CT::Object_CT(const int a_level,
                                Coordinatable&& a_coord,
                                Textable&& a_text) noexcept
    : BaseObject(getType(), a_level),
      Coordinatable(std::move(a_coord)),
      Textable(std::move(a_text))
{
}

int
game::obj::Object_CD::getType()
{
    return static_cast<int>(Type::COORDINATABLE | Type::Drawable);
}

int
game::obj::Object_CDH::getType()
{
    return static_cast<int>(Type::COORDINATABLE | Type::Drawable |
                            Type::Hitable);
}

int
game::obj::Object_CDT::getType()
{
    return static_cast<int>(Type::COORDINATABLE | Type::Drawable |
                            Type::Textable);
}

int
game::obj::Object_CDHT::getType()
{
    return static_cast<int>(Type::COORDINATABLE | Type::Drawable |
                            Type::Hitable | Type::Textable);
}

int
game::obj::Object_CT::getType()
{
    return static_cast<int>(Type::COORDINATABLE | Type::Textable);
}
