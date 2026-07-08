#include "typedef.hpp"

#include "gpu/window/window.hpp"

gpu::type::NDC
gpu::type::toNDC(const Coordinates& a_coord)
{
    auto win_size = window::Window::getSize();
    win_size /= 2;

    auto result = a_coord / win_size;
    result -= 1;
    return result;
}

gpu::type::Coordinates
gpu::type::toCoordinates(const NDC& a_ndc)
{
    auto win_size = window::Window::getSize();
    win_size *= (a_ndc + 1) / 2;
    return win_size;
}
