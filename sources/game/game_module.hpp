#pragma once

#include "kernel/framework/module/module.hpp"
#include "kernel/utility/type/declaration/lifecycle_manager.hpp"

#include "game_manager.hpp"

namespace game
{

class GameModule : public core::Module
{
public:
    GameModule();

protected:
    void initialize() override;
    bool loopBody() override;

private:
    utils::LifecycleManager<GameManager> m_game_manager;
};

} // namespace game
