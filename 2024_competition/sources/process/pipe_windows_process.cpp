#ifdef BILL_WINDOWS

#    include "pipe_windows_process.hpp"

//--------------------------------------------------------------------------------

#    include "domain/log.hpp"

//--------------------------------------------------------------------------------

#    define BUFFER_SIZE 65336 * 10

//--------------------------------------------------------------------------------

proc::PipeWindowsProcess::~PipeWindowsProcess()
{
    closeHandles();
}

//--------------------------------------------------------------------------------

void
proc::PipeWindowsProcess::IORedirection() noexcept
{
    // dom::writeInfo("Rederecting_input_and_output_to_pipe");

    mIOSet = true;

    SECURITY_ATTRIBUTES securatyAttributes;
    securatyAttributes.nLength              = sizeof(SECURITY_ATTRIBUTES);
    securatyAttributes.lpSecurityDescriptor = NULL;
    securatyAttributes.bInheritHandle       = true;

    if (!CreatePipe(&mChildSTDIN, &mThisSTDOUT, &securatyAttributes, 0))
    {
        dom::writeError("PipeProcess", "IORedirection", 20, "Can't_create_pipe",
                        "Windows");
    }

    if (!CreatePipe(&mThisSTDIN, &mChildSTDOUT, &securatyAttributes, 0))
    {
        dom::writeError("PipeProcess", "IORedirection", 21, "Can't_create_pipe",
                        "Windows");
    }

    ZeroMemory(&mStartupInfo, sizeof(STARTUPINFO));
    mStartupInfo.cb = sizeof(STARTUPINFO);
    mStartupInfo.dwFlags |= STARTF_USESTDHANDLES;

    mStartupInfo.hStdInput  = mChildSTDIN;
    mStartupInfo.hStdError  = mChildSTDOUT;
    mStartupInfo.hStdOutput = mChildSTDOUT;
}

//--------------------------------------------------------------------------------

void
proc::PipeWindowsProcess::readData(std::string& result) noexcept
{
    const size_t bufSize = 1024;
    char buf[bufSize];
    memset(buf, 0, bufSize - 1);
    unsigned long bread = 0;
    unsigned long avail = 0;

    while (bread == 0 && avail == 0)
    {
        PeekNamedPipe(mThisSTDIN, buf, bufSize - 1, &bread, &avail, NULL);
    }

    memset(buf, 0, sizeof(buf));
    bread = bufSize;
    result.clear();
    while (bread >= bufSize - 1)
    {
        memset(buf, 0, sizeof(buf));
        ReadFile(mThisSTDIN, buf, bufSize - 1, &bread, NULL);
        result += std::string(buf);
    }
}

//--------------------------------------------------------------------------------

void
proc::PipeWindowsProcess::writeData(const std::string& aMessage) noexcept
{
    unsigned long bread;
    WriteFile(mThisSTDOUT, aMessage.c_str(), aMessage.size(), &bread, NULL);
}

//--------------------------------------------------------------------------------

void
proc::PipeWindowsProcess::closeHandles() noexcept
{
    if (mIOSet)
    {
        CloseHandle(mChildSTDIN);
        CloseHandle(mChildSTDOUT);
    }
}

//--------------------------------------------------------------------------------

#endif // !BILL_WINDOWS
