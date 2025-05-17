#ifdef BILL_WINDOWS

#    include "windows_process.hpp"

//--------------------------------------------------------------------------------

#    include "general_tools/log.hpp"

//--------------------------------------------------------------------------------

proc::WindowsProcess::WindowsProcess() noexcept
{
    ZeroMemory(&mProcessInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&mStartupInfo, sizeof(STARTUPINFOA));
}

//--------------------------------------------------------------------------------

bool
proc::WindowsProcess::run() noexcept
{
    bool result = true;
    LOG_INFO("Runing_simple_windows_process");

    ResumeThread(mProcessInfo.hThread);
    WaitForSingleObject(mProcessInfo.hProcess, mTimeLimit);

    if (getExitCode(mProcessInfo.hProcess) == STILL_ACTIVE)
    {
        killProcess(mProcessInfo);
        result = false;
    }

    return result;
}

//--------------------------------------------------------------------------------

std::optional<proc::Limits>
proc::WindowsProcess::runWithLimits() noexcept
{
    LOG_INFO("Runing_windows_process_with_time_and_memory_evaluation");

    std::optional<Limits> result = {};

    uint64_t timeUsage   = 0;
    uint64_t memoryUsage = 0;

    uint64_t reservedTime = 200;
    uint64_t startTime    = 0;

    if (run())
    {
        long long endTime = 0;
        timeUsage         = endTime - startTime;
        result            = {timeUsage, memoryUsage};

        LOG_INFO("time_usage:", timeUsage);
        LOG_INFO("memory_usage:", memoryUsage);
    }

    return result;
}

//--------------------------------------------------------------------------------

void
proc::WindowsProcess::setComand(
    const std::vector<std::string>& aParameters) noexcept
{
    mProcessName = aParameters[0];
    for (auto& i : aParameters) mProcessArgs += i + " ";
    mProcessArgs.pop_back();
}

//--------------------------------------------------------------------------------

void
proc::WindowsProcess::create() noexcept
{
    LOG_INFO("Creating_windows_process_with_name:", mProcessName);
    LOG_INFO("Args:", mProcessArgs);

    IORedirection();

    char* name = (char*)mProcessName.c_str();
    if (mProcessName.empty()) name = NULL;
    if (CreateProcessA(name, (char*)mProcessArgs.c_str(), NULL, NULL, TRUE,
                       CREATE_UNICODE_ENVIRONMENT | CREATE_SUSPENDED |
                           CREATE_NO_WINDOW,
                       NULL, NULL, &mStartupInfo, &mProcessInfo) == FALSE)
    {
        LOG_ERROR("Process", "create", 10, "Can't_start_process",
                  "Name:", mProcessName, "Args:", mProcessArgs);

        // TODO:
        //  LOG_ERROR("Process", "create", 11,
        //                  base::Log::Message::globalMessages.GetLastWinAPIError());
    }
}

//--------------------------------------------------------------------------------
/*
** Next 5 functiona from Chinese tester
*/
//--------------------------------------------------------------------------------

long long
proc::WindowsProcess::getMillisecondsNow() noexcept
{
    static LARGE_INTEGER frequency;
    static BOOL useQpf = QueryPerformanceFrequency(&frequency);
    if (useQpf)
    {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000LL * now.QuadPart) / frequency.QuadPart;
    }
    else
    {
        return GetTickCount();
    }
    return 0;
}

//--------------------------------------------------------------------------------

long long
proc::WindowsProcess::getCurrentMemoryUsage(HANDLE& hProcess) noexcept
{
    PROCESS_MEMORY_COUNTERS pmc;
    long long currentMemoryUsage = 0;

    if (!GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
    {
        return 0;
    }
    currentMemoryUsage = pmc.PeakWorkingSetSize >> 10;

    if (currentMemoryUsage < 0)
    {
        currentMemoryUsage = INT_MAX >> 10;
    }
    return currentMemoryUsage;
}

//--------------------------------------------------------------------------------

long long
proc::WindowsProcess::getMaxMemoryUsage(PROCESS_INFORMATION& processInfo,
                                        long long memoryLimit) noexcept
{
    long long maxMemoryUsage = 0, currentMemoryUsage = 0;
    do
    {
        currentMemoryUsage = getCurrentMemoryUsage(processInfo.hProcess);
        if (currentMemoryUsage > maxMemoryUsage)
        {
            maxMemoryUsage = currentMemoryUsage;
        }
        if (memoryLimit != 0 && currentMemoryUsage > memoryLimit)
        {
            killProcess(processInfo);
        }
        Sleep(200);
    } while (getExitCode(processInfo.hProcess) == STILL_ACTIVE);
    return maxMemoryUsage;
}

//--------------------------------------------------------------------------------

DWORD
proc::WindowsProcess::getExitCode(HANDLE& hProcess) noexcept
{
    DWORD exitCode = 0;
    GetExitCodeProcess(hProcess, &exitCode);
    return exitCode;
}

//--------------------------------------------------------------------------------

bool
proc::WindowsProcess::killProcess(PROCESS_INFORMATION& processInfo) noexcept
{
    LOG_INFO("Killing_process");

    DWORD processId             = processInfo.dwProcessId;
    PROCESSENTRY32 processEntry = {0};
    processEntry.dwSize         = sizeof(PROCESSENTRY32);
    HANDLE handleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(handleSnap, &processEntry))
    {
        BOOL isContinue = TRUE;

        do
        {
            if (processEntry.th32ParentProcessID == processId)
            {
                HANDLE hChildProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE,
                                                   processEntry.th32ProcessID);
                if (hChildProcess)
                {
                    TerminateProcess(hChildProcess, 1);
                    CloseHandle(hChildProcess);
                }
            }
            isContinue = Process32Next(handleSnap, &processEntry);
        } while (isContinue);

        HANDLE hBaseProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
        if (hBaseProcess)
        {
            TerminateProcess(hBaseProcess, 1);
            CloseHandle(hBaseProcess);
        }
    }

    if (getExitCode(processInfo.hProcess) == STILL_ACTIVE)
    {
        return false;
    }

    LOG_INFO("Process killed?");

    return true;
}

//--------------------------------------------------------------------------------

#endif // !BILL_WINDOWS
