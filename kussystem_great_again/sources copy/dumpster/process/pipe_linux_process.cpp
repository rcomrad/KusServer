#include "pipe_linux_process.hpp"

#ifdef LINUS_LINUX

//--------------------------------------------------------------------------------

#    include <boost/date_time.hpp>
#    include <sys/resource.h>
#    include <sys/time.h>
#    include <sys/types.h>

#    include <cstring>
#    include <fcntl.h>
#    include <signal.h>
#    include <unistd.h>
#    include <wait.h>

#    include "domain/log.hpp"

//--------------------------------------------------------------------------------

proc::PipeLinuxProcess::PipeLinuxProcess(const PipeLinuxProcess& other) noexcept
{
    *this = other;
}

proc::PipeLinuxProcess&
proc::PipeLinuxProcess::operator=(const PipeLinuxProcess& other) noexcept
{
    mParameters = other.mParameters;
    // getRawParameters();
    return *this;
}

//--------------------------------------------------------------------------------

proc::PipeLinuxProcess::~PipeLinuxProcess() noexcept
{
    for (auto i : mRawParameters)
    {
        if (i != NULL) delete[] i;
    }

    std::cout << "kill: " << kill(mChildPID, SIGKILL) << "\n";
    // std::cout << "kill: " << kill(-mChildPID, SIGKILL) << "\n";

    wait(NULL);

    close(mPipeA[0]);
    close(mPipeA[1]);
    close(mPipeB[0]);
    close(mPipeB[1]);
}

//--------------------------------------------------------------------------------

void
proc::PipeLinuxProcess::setComand(
    const std::vector<str::String>& aParameters) noexcept
{
    mParameters = aParameters;
    // getRawParameters();
}

//--------------------------------------------------------------------------------

void
proc::PipeLinuxProcess::create() noexcept
{
    kill(mChildPID, SIGKILL);
    // kill(-mChildPID, SIGKILL);
    IORedirection();
    makeParameters();
    LOG_INFO("Creating_process_with_name:", mRawParameters[0]);

    mChildPID = fork();
    if (mChildPID == -1)
    {
        LOG_ERROR("PipeProcess", 10, "Linux", "Can't_create_process");
    }
    else if (!mChildPID)
    {
        dup2(mPipeA[0], STDIN_FILENO);
        dup2(mPipeB[1], STDOUT_FILENO);

        close(mPipeA[1]);
        close(mPipeB[0]);

        // auto itt = &mRawParameters[0];
        execvp(mRawParameters[0], &mRawParameters[0]);
    }
    else
    {
        std::cout << "chiled_id : " << mChildPID << "\n";
        close(mPipeA[0]);
        close(mPipeB[1]);
    }
}

//--------------------------------------------------------------------------------

bool
proc::PipeLinuxProcess::run() noexcept
{
    LOG_INFO("Runing_simple_process");
    wait(NULL);
    return true;
}
//--------------------------------------------------------------------------------

std::optional<proc::Limits>
proc::PipeLinuxProcess::runWithLimits() noexcept
{
    LOG_INFO("Runing_process_with_time_and_memory_evaluation");

    std::optional<Limits> result = {};

    uint64_t timeUsage   = 0;
    uint64_t memoryUsage = 0;

    rusage resourseUsage;
    int status;
    // wait4(mChildPID, &status, 0, &resourseUsage);
    boost::posix_time::ptime timeLocal =
        boost::posix_time::second_clock::local_time();

    for (uint64_t i = 0;; ++i)
    {
        if (wait4(mChildPID, &status, WNOHANG, &resourseUsage) != 0) break;

        boost::posix_time::ptime timeLocal2 =
            boost::posix_time::second_clock::local_time();
        auto dur = timeLocal2 - timeLocal;
        if (dur.seconds() > 6) break;
    }
    std::cout << "kill " << mRawParameters[0] << ": "
              << kill(mChildPID, SIGKILL) << "\n";
    // std::cout << "kill " << mRawParameters[0] << ": "
    //           << kill(-mChildPID, SIGKILL) << "\n";

    timeUsage += resourseUsage.ru_utime.tv_sec * 1'000'000;
    timeUsage += resourseUsage.ru_utime.tv_usec;
    timeUsage += resourseUsage.ru_stime.tv_sec * 1'000'000;
    timeUsage += resourseUsage.ru_stime.tv_usec;
    timeUsage /= 1000;

    LOG_INFO("status:", status);
    LOG_INFO("WIFEXITED:", WIFEXITED(status));
    LOG_INFO("WEXITSTATUS:", WEXITSTATUS(status));
    LOG_INFO("WIFSIGNALED:", WIFSIGNALED(status));
    LOG_INFO("WTERMSIG:", WTERMSIG(status));
    LOG_INFO("WIFSTOPPED:", WIFSTOPPED(status));

    LOG_INFO("time_usage:", timeUsage);
    LOG_INFO("memory_usage:", memoryUsage);

    if (WIFEXITED(status))
    {
        result = {timeUsage, memoryUsage};
    }
    return result;
}

//--------------------------------------------------------------------------------

#    define BUFFER_SIZE 65336 * 10

//--------------------------------------------------------------------------------

void
proc::PipeLinuxProcess::IORedirection() noexcept
{
    LOG_INFO("Rederecting_input_and_output_to_pipe");

    close(mPipeA[0]);
    close(mPipeA[1]);
    close(mPipeB[0]);
    close(mPipeB[1]);

    // mPipeA[0] = 0;
    // mPipeA[1] = 0;
    // mPipeB[0] = 0;
    // mPipeB[1] = 0;

    pipe2(mPipeA, 0);
    pipe2(mPipeB, 0);

    // close(pfd[1]); // Child, close write end of pipe
    // dup2(pfd[0], STDIN_FILENO);
    // dup2(mPipeA[0], STDIN_FILENO);
    // dup2(mPipeB[1], STDOUT_FILENO);

    fcntl(mPipeA[0], F_SETPIPE_SZ, BUFFER_SIZE);
    fcntl(mPipeA[1], F_SETPIPE_SZ, BUFFER_SIZE);
    fcntl(mPipeB[0], F_SETPIPE_SZ, BUFFER_SIZE);
    fcntl(mPipeB[1], F_SETPIPE_SZ, BUFFER_SIZE);

    // // fcntl(mPipeA[0], F_SETFL, O_NONBLOCK);
    // // fcntl(mPipeA[1], F_SETFL, O_NONBLOCK);
    // fcntl(mPipeB[0], F_SETFL, O_NONBLOCK);
    // // fcntl(mPipeB[1], F_SETFL, O_NONBLOCK);
}

//--------------------------------------------------------------------------------
#    include <poll.h>
void
proc::PipeLinuxProcess::readData(char* result) noexcept
{
    // result.clear();
    // char buf[1024];
    // memset(buf, 0, sizeof(buf));

    // // while (read(mPipeB[0], &buf, 1024) == 1024)
    // // {
    // //     result += str::String(buf);
    // //     memset(buf, 0, sizeof(buf));
    // // }
    // // result += str::String(buf);

    // boost::posix_time::ptime timeLocal =
    //     boost::posix_time::second_clock::local_time();

    // int count = 0;
    // while ((count = read(mPipeB[0], &buf, 1024)) == 1024 || count == 0)
    // {
    //     result += str::String(buf);
    //     memset(buf, 0, sizeof(buf));

    //     boost::posix_time::ptime timeLocal2 =
    //         boost::posix_time::second_clock::local_time();
    //     auto dur = timeLocal2 - timeLocal;
    //     if (dur.seconds() > 6) break;
    // }
    // result += str::String(buf);

    //===================================================

    struct pollfd fds;

    // от sock1 мы будем ожидать входящих данных
    fds.fd     = mPipeB[0];
    fds.events = POLLIN;

    // ждём до 10 секунд
    int ret = poll(&fds, 2, 5000);
    // проверяем успешность вызова
    if (ret == 0)
    { // таймаут, событий не произошло
    }
    else
    {
        result.clear();
        char buf[1024];
        memset(buf, 0, sizeof(buf));

        while (read(mPipeB[0], &buf, 1024) == 1024)
        {
            result += str::String(buf);
            memset(buf, 0, sizeof(buf));
        }

        result += str::String(buf);
    }
}

//--------------------------------------------------------------------------------

void
proc::PipeLinuxProcess::writeData(const char* aMessage) noexcept
{
    write(mPipeA[1], aMessage.c_str(), aMessage.size());
}

//--------------------------------------------------------------------------------

// void
// proc::PipeLinuxProcess::getRawParameters() noexcept
// {
//     for (auto& s : mParameters)
//     {
//         mRawParameters.emplace_back((char*)s.c_str());
//     }
//     mRawParameters.push_back(NULL);
// }

void
proc::PipeLinuxProcess::makeParameters() noexcept
{
    LOG_INFO("makeParameters entry");
    for (auto i : mRawParameters)
    {
        if (i != NULL) delete[] i;
    }

    mRawParameters.resize(0);
    mRawParameters.reserve(mParameters.size() + 1);
    for (auto& s : mParameters)
    {
        mRawParameters.emplace_back(new char[s.size() + 1]);
        strcpy(mRawParameters.back(), s.c_str());
    }
    mRawParameters.emplace_back();
    mRawParameters.back() = NULL;
    LOG_INFO("makeParameters exit");
}

//--------------------------------------------------------------------------------

#endif // !LINUS_LINUX
