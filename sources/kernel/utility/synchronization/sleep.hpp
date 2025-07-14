#pragma once

//--------------------------------------------------------------------------------

namespace util
{
class Sleep
{
public:
    static void large() noexcept;
    static void medium() noexcept;
    static void small() noexcept;
    static void yield() noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
