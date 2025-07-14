#include "state.hpp"

#include <vector>

const std::string&
core::getStateName(State a_state) noexcept
{

    static std::vector<std::string> g_state_types = {"nun",
                                                     "awaiting",
                                                     "reconstruction",
                                                     "created",
                                                     "initiakize",
                                                     "alive",
                                                     "alive_with_exceptions",
                                                     "closing",
                                                     "terminated",
                                                     "killed",
                                                     "idle",
                                                     "singleton_error"};
    using StateType = std::underlying_type_t<State>;
    return g_state_types[static_cast<StateType>(a_state)];
}
