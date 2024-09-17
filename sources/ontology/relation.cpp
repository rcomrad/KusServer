#include "relation.hpp"

#define RELATION_DECLARE(value) #value,
const char*
onto::getRelationStr(Relation a_relation) noexcept
{
    static const char* names[RELATION_COUNT] = {
#include "relation.inc"
    };
    return names[static_cast<int>(a_relation)];
}

int
onto::getOpposite(Relation a_relation) noexcept
{
    constexpr int middle = static_cast<int>(Relation::MIDDLE);

    int result = static_cast<int>(a_relation);
    if (result > middle)
    {
        result -= middle;
    }
    else
    {
        result += middle;
    }
    return result;
}
