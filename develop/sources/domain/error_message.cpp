#include "error_message.hpp"

//--------------------------------------------------------------------------------

#include <iostream>

//--------------------------------------------------------------------------------

dom::Message dom::Message::globalMessages;

//--------------------------------------------------------------------------------

dom::Message::Message() noexcept
{
    mLogBlockCount = 0;

#if defined(LOGS_DEFAULT_OUTPUT)
    mLogStream = &std::cout;
#elif defined(LOGS_TO_COUT_OUTPUT)
    mLogStream   = &std::cout;
#elif defined(LOGS_TO_FILE_OUTPUT)
    // auto sss     = LOGS_PATH + "out.log";
    // mLogStream   = new std::ofstream(LOGS_PATH + "out.log");
#endif

#if defined(ERRORS_DEFAULT_OUTPUT)
    mErrorStream = &std::cout;
#elif defined(ERRORS_TO_COUT_OUTPUT)
    mErrorStream = &std::cout;
#elif defined(ERRORS_TO_FILE_OUTPUT)
    // mErrorStream = new std::ofstream(ERRORS_PATH + "out.err");
#elif defined(ERRORS_TO_LOG_OUTPUT)
    mErrorStream = mLogStream;
#endif
}

//--------------------------------------------------------------------------------

void
dom::Message::writeLogEndl() noexcept
{
    (*mLogStream) << '\n';
}

//--------------------------------------------------------------------------------

#ifdef BILL_WINDOWS
#    include <windows.h>
#endif

//--------------------------------------------------------------------------------

#ifdef BILL_WINDOWS
std::string
dom::Message::GetLastWinAPIError() noexcept
{
    std::string result;

    // Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID != 0)
    {
        LPSTR messageBuffer = nullptr;

        /*
        **Ask Win32 to give us the string version of that message ID.
        ** The parameters we pass in, tell Win32 to create the buffer
        ** that holds the message for us
        ** (because we don't yet know how long the message string will be).
        */
        size_t size = FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR)&messageBuffer, 0, NULL);

        // Copy the error message into a std::string.
        for (size_t i = 0; i < size; ++i)
        {
            result.push_back(messageBuffer[i]);
        }

        // Free the Win32's string's buffer.
        LocalFree(messageBuffer);
    }

    return result;
}
#endif // !BILL_WINDOWS

//--------------------------------------------------------------------------------
