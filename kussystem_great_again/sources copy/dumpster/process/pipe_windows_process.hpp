#ifndef WINDOWS_PIPE_PROCESS_HPP
#define WINDOWS_PIPE_PROCESS_HPP

#ifdef BILL_WINDOWS

//--------------------------------------------------------------------------------

#    include "windows_process.hpp"

namespace proc
{
class PipeWindowsProcess : public WindowsProcess
{
public:
    PipeWindowsProcess() noexcept = default;
    virtual ~PipeWindowsProcess();

    PipeWindowsProcess(const PipeWindowsProcess& other) noexcept = default;
    PipeWindowsProcess& operator=(const PipeWindowsProcess& other) noexcept =
        default;

    PipeWindowsProcess(PipeWindowsProcess&& other) noexcept = default;
    PipeWindowsProcess& operator=(PipeWindowsProcess&& other) noexcept =
        default;

    virtual void IORedirection() noexcept final override;
    void readData(char* result) noexcept final override;
    void writeData(const char* aMessage) noexcept final override;

private:
    bool mIOSet = false;
    HANDLE mThisSTDIN;
    HANDLE mThisSTDOUT;
    HANDLE mChildSTDIN;
    HANDLE mChildSTDOUT;

    virtual void closeHandles() noexcept;
};
} // namespace proc

//--------------------------------------------------------------------------------

#endif // !BILL_WINDOWS

#endif // !WINDOWS_PIPE_PROCESS_HPP
