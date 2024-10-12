#pragma once

namespace onto
{

#define RELATION_DECLARE(value) value,
enum class Relation
{
#include "relation.inc"
};

constexpr int RELATION_COUNT = (static_cast<int>(Relation::MAX) + 1);

const char*
getRelationName(int a_relation) noexcept;

const char*
getRelationName(Relation a_relation) noexcept;

int
getOpposite(Relation a_relation) noexcept;

} // namespace onto
