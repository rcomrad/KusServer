#include "core/module/module.hpp"

#include "utility/common/holy_trinity.hpp"

#include "app.hpp"

namespace kusengine
{
class Engine : public core::Module
{
public:
    HOLY_TRINITY_SINGLETON(Engine);

    bool loopBody() noexcept override;

    // void initialize() noexcept override;

    void run() noexcept override;
    // void commandSetup() const noexcept override;
    // void variableSetup() const noexcept override;

private:
    Engine() noexcept;

    App m_app;
};
}; // namespace kusengine
