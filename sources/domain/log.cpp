#include "log.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "core/variable_storage.hpp"

dom::Log::Log() noexcept
{
    mIsFileOutput = false;
    mStatus       = PrintStatus::Info;
    mStreams      = &std::cout;
}

dom::Log::~Log()
{
    if (mIsFileOutput)
    {
        delete mStreams;
    }
}

dom::Log&
dom::Log::getInstance() noexcept
{
    static Log instance;
    return instance;
}

void
dom::Log::reloadSettings() noexcept
{
    static std::unordered_map<std::string, PrintStatus> statusMap = {
        {"info",    PrintStatus::Info   },
        {"warning", PrintStatus::Warning},
        {"error",   PrintStatus::Error  }
    };

    auto statusType = core::VariableStorage::touchWord("log_type");
    if (!statusType.empty())
    {
        auto it = statusMap.find(statusType);
        if (it != statusMap.end())
        {
            mStatus = it->second;
            writeInfo("Log setting changed (", it->first, ")");
        }
        else
        {
            writeError("No such log setting (", statusType, ")");
        }
    }
    else
    {
        writeWarning("No log setting, default setting applied (info)");
    }

    auto buffer = core::VariableStorage::touchWord("log_buffer");
    if (!buffer.empty())
    {
        if (buffer == "cout")
        {
            mIsFileOutput = false;
            mStreams      = &std::cout;

            writeInfo("Log buffer changed to stdout");
        }
        else if (buffer == "cerr")
        {
            mIsFileOutput = false;
            mStreams      = &std::cerr;

            writeInfo("Log buffer changed to stderr");
        }
        else
        {
            mIsFileOutput = true;
            mStreams      = new std::ofstream(buffer);

            writeInfo("Log buffer changed to ", buffer, " file");
        }
    }
    else
    {
        writeWarning("No log buffer, default setting applied (cout)");
    }
}

// #ifdef BILL_WINDOWS
// #    include <windows.h>
// #endif

// #ifdef BILL_WINDOWS
// std::string
// dom::Message::GetLastWinAPIError() noexcept
// {
//     std::string result;

//     // Get the error message ID, if any.
//     DWORD errorMessageID = ::GetLastError();
//     if (errorMessageID != 0)
//     {
//         LPSTR messageBuffer = nullptr;

//         /*
//         **Ask Win32 to give us the string version of that message ID.
//         ** The parameters we pass in, tell Win32 to create the buffer
//         ** that holds the message for us
//         ** (because we don't yet know how long the message string will be).
//         */
//         size_t size = FormatMessageA(
//             FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
//                 FORMAT_MESSAGE_IGNORE_INSERTS,
//             NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//             (LPSTR)&messageBuffer, 0, NULL);

//         // Copy the error message into a std::string.
//         for (size_t i = 0; i < size; ++i)
//         {
//             result.push_back(messageBuffer[i]);
//         }

//         // Free the Win32's string's buffer.
//         LocalFree(messageBuffer);
//     }

//     return result;
// }
// #endif // !BILL_WINDOWS
