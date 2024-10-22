#include "relation.hpp"

const char*
onto::getRelationName(int a_relation) noexcept
{
    return getRelationName(Relation(a_relation));
}

#define RELATION_DECLARE(value) #value,
const char*
onto::getRelationName(Relation a_relation) noexcept
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
