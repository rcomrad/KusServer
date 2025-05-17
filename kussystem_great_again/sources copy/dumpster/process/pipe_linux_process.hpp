#ifndef PIPE_LINUX_PROCESS_HPP
#define PIPE_LINUX_PROCESS_HPP

#ifdef LINUS_LINUX

//--------------------------------------------------------------------------------

#    include <string>

#    include "base_process.hpp"

namespace proc
{
class PipeLinuxProcess : public BaseProcess
{
public:
    PipeLinuxProcess() noexcept = default;
    virtual ~PipeLinuxProcess();

    PipeLinuxProcess(const PipeLinuxProcess& other) noexcept;
    PipeLinuxProcess& operator=(const PipeLinuxProcess& other) noexcept;

    PipeLinuxProcess(PipeLinuxProcess&& other) noexcept            = default;
    PipeLinuxProcess& operator=(PipeLinuxProcess&& other) noexcept = default;

    void setComand(
        const std::vector<str::String>& aParameters) noexcept final override;

    void create() noexcept final override;

    bool run() noexcept final override;
    std::optional<Limits> runWithLimits() noexcept final override;

    virtual void IORedirection() noexcept;
    void readData(char* result) noexcept final override;
    void writeData(const char* aMessage) noexcept final override;

private:
    std::vector<str::String> mParameters;
    std::vector<char*> mRawParameters;

    int mChildPID = 2e9;

    int mPipeA[2];
    int mPipeB[2];

    void makeParameters() noexcept;
    // void getRawParameters() noexcept;
};
} // namespace proc

//--------------------------------------------------------------------------------

#endif // !LINUS_LINUX

#endif // !PIPE_LINUX_PROCESS_HPP