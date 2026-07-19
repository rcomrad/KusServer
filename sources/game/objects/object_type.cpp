#include "object_type.hpp"

int
game::obj::generateTypeMask(const std::unordered_set<std::string>& a_type_flags)
{
    // TODO: C++26 reflection
    int result = 0;
    for (auto& i : a_type_flags)
    {
        if (i == "coord") result |= Type::COORDINATABLE;
        else if (i == "draw") result |= Type::DRAWABLE;
        else if (i == "hit") result |= Type::HITABLE;
        else if (i == "text") result |= Type::TEXTABLE;
        else THROW("Unrecognized object flag '%s'", i);
    }
    return result;
}
