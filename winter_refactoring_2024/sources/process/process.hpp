#ifndef PROCESS_HPP
#define PROCESS_HPP

//--------------------------------------------------------------------------------

#include "bst_process.hpp"
#include "pipe_linux_process.hpp"
#include "pipe_windows_process.hpp"

//--------------------------------------------------------------------------------

namespace proc
{
#if defined(BOOST_PROCESS)
class Process : public BoostProcess
#elif defined(BILL_WINDOWS)
class Process : public PipeWindowsProcess
#elif defined(LINUS_LINUX)
class Process : public PipeLinuxProcess
#endif
{
public:
    Process() noexcept = default;
    virtual ~Process() = default;

    Process(const Process& other) noexcept            = default;
    Process& operator=(const Process& other) noexcept = default;

    Process(Process&& other) noexcept            = default;
    Process& operator=(Process&& other) noexcept = default;
};
} // namespace proc

//--------------------------------------------------------------------------------

#endif // !PROCESS_HPP
