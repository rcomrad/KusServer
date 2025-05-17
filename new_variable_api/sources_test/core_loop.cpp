// #include "core_loop.hpp"

// #include "core/core.hpp"
// #include "core/variable_storage.hpp"

// kustest::CoreLoop::CoreLoop() noexcept
// {
//     core::Core::setup();
//     m_core_thread = std::thread([] { core::Core::run(); });
// }

// kustest::CoreLoop::~CoreLoop() noexcept
// {
//     core::VariableStorage::set(0, 0);
//     m_core_thread.join();
// }
