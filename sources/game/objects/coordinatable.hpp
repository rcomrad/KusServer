#pragma once

#include "gpu/sprite/sprite_view.hpp"
#include "gpu/utils/typedef.hpp"

namespace game::obj
{

class ObjectInfo;

class Coordinatable
{
public:
    Coordinatable(const ObjectInfo& a_info);
    Coordinatable(Coordinatable&& a_other) noexcept = default;

    void setPosition(const gpu::type::Coordinates& a_pos);
    void movePosition(const gpu::type::Coordinates& a_delta_pos);
    void repositionForNewWindow(const gpu::type::CoordinateSize& a_old_window,
                                const gpu::type::CoordinateSize& a_new_window);

    const gpu::type::Coordinates& getPosition() const;

private:
    gpu::type::Coordinates m_pos;
};

} // namespace game::obj
