#include "pipe_linux_process.hpp"

#ifdef LINUS_LINUX

//--------------------------------------------------------------------------------

#include <cstring>
#include <wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "domain/error_message.hpp"

//--------------------------------------------------------------------------------

proc::PipeLinuxProcess::PipeLinuxProcess(const PipeLinuxProcess& other)  noexcept
{
    *this = other;
}

//--------------------------------------------------------------------------------

proc::PipeLinuxProcess&
proc::PipeLinuxProcess::operator=(const PipeLinuxProcess& other) noexcept
{
    mParameters.reserve(other.mParameters.size());
    for(auto& str : other.mParameters) mParameters.emplace_back(str.getCopy());
    getRawParameters();
    return *this;
}

//--------------------------------------------------------------------------------

void 
proc::PipeLinuxProcess::setComand(dom::CharArrayTable&& aParameters) noexcept
{
    mParameters = std::move(aParameters);
    getRawParameters();
}

//--------------------------------------------------------------------------------

void
proc::PipeLinuxProcess::create() noexcept
{
    WRITE_LOG("Creating_process_with_name:", mRawParameters[0]);

    IORedirection();

    mChildPID = fork();
    if (mChildPID == -1)
    {
        WRITE_ERROR("PipeProcess", 10, "Linux", "Can't_create_process");
    }
    else if (!mChildPID)
    {
        dup2(mPipeA[0], STDIN_FILENO);
        dup2(mPipeB[1], STDOUT_FILENO);
        auto itt  = &mRawParameters[0];
        execvp(mRawParameters[0], &mRawParameters[0]);
    }
    else
    {
    }
}

//--------------------------------------------------------------------------------

bool
proc::PipeLinuxProcess::run() noexcept
{
    WRITE_LOG("Runing_simple_process");
    wait(NULL);
    return true;
}

//--------------------------------------------------------------------------------

std::optional<dom::Pair<uint64_t>> 
proc::PipeLinuxProcess::runWithLimits() noexcept
{
    START_LOG_BLOCK("Runing_process_with_time_and_memory_evaluation");

    std::optional<dom::Pair<uint64_t>> result = {}; 

    uint64_t timeUsage = 0;
    uint64_t memoryUsage = 0;

    rusage resourseUsage;
    int status;
    wait4(mChildPID, &status, 0, &resourseUsage);
    int gg = WIFEXITED(status);

    timeUsage += resourseUsage.ru_utime.tv_sec * 1000000L;
    timeUsage += resourseUsage.ru_utime.tv_usec;
    timeUsage += resourseUsage.ru_stime.tv_sec * 1000000L;
    timeUsage += resourseUsage.ru_stime.tv_usec;

    WRITE_LOG("status:",            status);
    WRITE_LOG("WIFEXITED:",         WIFEXITED(status));
    WRITE_LOG("WEXITSTATUS:",       WEXITSTATUS(status));
    WRITE_LOG("WIFSIGNALED:",       WIFSIGNALED(status));
    WRITE_LOG("WTERMSIG:",          WTERMSIG(status));
    WRITE_LOG("WIFSTOPPED:",        WIFSTOPPED(status));

    WRITE_LOG       ("time_usage:",    timeUsage);
    END_LOG_BLOCK   ("memory_usage:",  memoryUsage);

    if (WIFEXITED(status)) 
    {
        result = {timeUsage, memoryUsage};
    }
    return result;
}

//--------------------------------------------------------------------------------

#define BUFFER_SIZE 65336 * 10

//--------------------------------------------------------------------------------

void
proc::PipeLinuxProcess::IORedirection() noexcept
{
    WRITE_LOG("Rederecting_input_and_output_to_pipe");

    pipe(mPipeA);
    pipe(mPipeB);


    fcntl(mPipeA[0], F_SETPIPE_SZ, BUFFER_SIZE);
    fcntl(mPipeA[1], F_SETPIPE_SZ, BUFFER_SIZE);
    fcntl(mPipeB[0], F_SETPIPE_SZ, BUFFER_SIZE);
    fcntl(mPipeB[1], F_SETPIPE_SZ, BUFFER_SIZE);
}

//--------------------------------------------------------------------------------

void
proc::PipeLinuxProcess::readData(std::string& result) noexcept
{
    result.clear();
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    while (read(mPipeB[0], &buf, 1024) == 1024)
    {
        result += std::string(buf);
        memset(buf, 0, sizeof(buf));
    }
    result += std::string(buf);
}

//--------------------------------------------------------------------------------

void
proc::PipeLinuxProcess::writeData(const std::string& aMessage) noexcept
{
    write(mPipeA[1], aMessage.c_str(), aMessage.size());
}

//--------------------------------------------------------------------------------

void
proc::PipeLinuxProcess::getRawParameters() noexcept
{
    mRawParameters.reserve(mParameters.size());
    for(auto& ptr : mParameters)
    {
        mRawParameters.emplace_back(ptr);
    }
    mRawParameters.push_back(NULL);
}

//--------------------------------------------------------------------------------

#endif // !LINUS_LINUX
