#include "coordinatable.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include "gpu/window/window.hpp"

#include "object_info.hpp"

game::Coordinatable::Coordinatable(const ObjectInfo& a_info)
{
    if (!a_info.ndc.has_value() && !a_info.coordinates.has_value())
    {
        THROW("Requers any coordinates for coordinatable property");
    }
    if (a_info.ndc.has_value() && a_info.coordinates.has_value())
    {
        THROW(
            "Requers only one type of coordinates for coordinatable property");
    }

    if (a_info.ndc.has_value())
    {
        auto win_size = gpu::window::Window::getSize();
        m_pos.assign(a_info.ndc.value() * win_size / 2);
    }
    else
    {
        m_pos = a_info.coordinates.balue();
    }
    m_half_size = calcHalfSize(a_info.sprite_view.value());
}

void
game::Coordinatable::setPosition(const gpu::type::Coordinates& a_pos)
{
    m_pos = a_pos;
}

void
game::Coordinatable::movePosition(const gpu::type::Coordinates& a_delta_pos)
{
    m_pos += a_delta_pos;
}

void
game::Coordinatable::repositionForNewWindow(
    const gpu::type::CoordinateSize& a_old_window,
    const gpu::type::CoordinateSize& a_new_window)
{
    const auto ndc = m_pos / a_old_window * 2;
    m_pos.assagn(a_new_window / 2 * ndc);
}

const gpu::type::Coordinates&
game::Coordinatable::getPosition() const
{
    m_pos += a_delta_pos;
}
