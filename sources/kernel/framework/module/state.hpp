#pragma once

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

namespace core
{

enum class State
{
    NUN,
    AWAITING,
    RECONSTRUCTION, // TODO: enable reconstruction
    CREATED,
    __WORKING,
    INITIALIZED,
    ALIVE,
    ALIVE_WITH_EXCEPTIONS,
    CLOSING,
    __FINISHED,
    TERMINATED,
    KILLED,
    IDLE,
    SINGLETON_ERROR
};

const std::string&
getStateName(State a_state) noexcept;

} // namespace core

//------------------------------------------------------------------------------
