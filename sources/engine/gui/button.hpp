#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "engine/render_objects/drawable.hpp"

namespace gui
{
class Button : public Drawable
{
public:
    Button(float x, float y, std::string_view texture_name);

private:
};
}; // namespace gui

#endif // BUTTON_HPP
