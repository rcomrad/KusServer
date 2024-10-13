#pragma once

//--------------------------------------------------------------------------------

#include "core/module/module.hpp"

//--------------------------------------------------------------------------------

namespace olymp
{
class Olymp : public core::Module
{
public:
    HOLY_TRINITY_SINGLETON(Olymp);
    ~Olymp() override = default;

    bool loopBody() noexcept override;
    void commandSetup() const noexcept override;
    void variableSetup() const noexcept override;

private:
    Olymp() noexcept;
};

} // namespace olymp

//--------------------------------------------------------------------------------
