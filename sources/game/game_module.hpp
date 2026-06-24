#pragma once

#include "kernel/framework/module/include_me.hpp"

namespace game
{

class GameModule : public core::Module
{
public:
    GameModule();

protected:
    void initialize() override;
    bool loopBody() override;
};

} // namespace game
