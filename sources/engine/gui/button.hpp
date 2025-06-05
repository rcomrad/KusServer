#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "engine/drawable/drawable.hpp"

namespace kusengine
{
class Button : public Drawable
{
public:
    Button(const glm::vec2& position, const glm::vec2& size);

private:
};
}; // namespace kusengine

#endif // BUTTON_HPP
