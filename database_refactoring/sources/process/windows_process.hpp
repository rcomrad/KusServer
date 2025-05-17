#ifndef WINDOWS_PROCESS_HPP
#define WINDOWS_PROCESS_HPP

#ifdef BILL_WINDOWS

//--------------------------------------------------------------------------------

#include "base_process.hpp"

//--------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <atlalloc.h>
#include <atlconv.h>
#include <cstdint>
#include <psapi.h>
#include <shlwapi.h>
#include <string>
#include <tlhelp32.h>
#include <userenv.h>
#include <windows.h>

//--------------------------------------------------------------------------------

namespace proc
{
class WindowsProcess : public BaseProcess
{
public:
    /*
    \brief Base process constructor that initialize time and memory
        usage limits for child process.
        (all child process have max time and memory usage limits
        that defined in MAX_TIME_LIMIT and MAX_MEMORY_LIMIT)
    */
    WindowsProcess() noexcept;
    virtual ~WindowsProcess() = default;

    WindowsProcess(const WindowsProcess& other) noexcept            = default;
    WindowsProcess& operator=(const WindowsProcess& other) noexcept = default;

    WindowsProcess(WindowsProcess&& other) noexcept            = default;
    WindowsProcess& operator=(WindowsProcess&& other) noexcept = default;

    void setComand(
        const std::vector<std::string>& aParameters) noexcept final override;

    /*
    \brief Create a child process with the specified parameters.
    */
    void create() noexcept final override;

    /*
    \brief Executing the child process without time and memory
        usage evaluation.
    \return Returns true if the process is completed successfully.
    */
    bool run() noexcept final override;

    /*
    \brief Executing the child process with time and memory
        usage evaluation.
    \return Returns the time and memory used by the process if
        the process is completed successfully.
    */
    std::optional<Limits> runWithLimits() noexcept final override;

protected:
    STARTUPINFOA mStartupInfo;
    PROCESS_INFORMATION mProcessInfo;

    /*
    \brief Redirecting input and output streams for a child process.
    */

    /*
    \brief Closes the input and output handler for the child process.
        (finishing of communication with the child process)
    */
    virtual void closeHandles() noexcept = 0;

private:
    std::string mProcessName;
    std::string mProcessArgs;

    long long getMillisecondsNow() noexcept;

    long long getCurrentMemoryUsage(HANDLE&) noexcept;
    long long getMaxMemoryUsage(PROCESS_INFORMATION&, long long) noexcept;

    DWORD getExitCode(HANDLE&) noexcept;
    bool killProcess(PROCESS_INFORMATION&) noexcept;
};

} // namespace proc

#undef max
#undef min

//--------------------------------------------------------------------------------

#endif // !BILL_WINDOWS

#endif // !WINDOWS_PROCESS_HPP
