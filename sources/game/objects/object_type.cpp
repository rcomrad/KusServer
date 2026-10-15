#include "object_type.hpp"

#include "kernel/framework/logger/basic/exception.hpp"

int
game::obj::generateTypeMask(const std::unordered_set<std::string>& a_type_flags)
{
    // TODO: C++26 reflection
    int result = 0;
    for (auto& i : a_type_flags)
    {
        if (i == "coord") result |= static_cast<int>(Type::COORDINATABLE);
        else if (i == "draw") result |= static_cast<int>(Type::DRAWABLE);
        else if (i == "hit") result |= static_cast<int>(Type::HITABLE);
        else if (i == "text") result |= static_cast<int>(Type::TEXTABLE);
        else THROW("Unrecognized object flag '%s'", i);

        // TODO: maybe make different exception classes?
    }
    return result;
}
