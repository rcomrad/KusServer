#include "log.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "domain/variable_storage.hpp"

//--------------------------------------------------------------------------------

route::RouterNode gen::Log::mNode("general", "log", (void*) &gen::Log::applyCommand);

//--------------------------------------------------------------------------------

gen::Log::Log() noexcept
{
    mIsFileOutput = false;
    mStatus       = PrintStatus::Info;
    mStreams      = &std::cout;
}

gen::Log::~Log()
{
    clear();
}

void
gen::Log::clear() noexcept
{

    if (mIsFileOutput)
    {
        delete mStreams;
        mIsFileOutput = false;
    }
}

gen::Log&
gen::Log::getInstance() noexcept
{
    static Log instance;
    return instance;
}

//--------------------------------------------------------------------------------

void
gen::Log::reloadFromSettings() noexcept
{
    auto log = dom::VariableStorage::touchWord(std::string("log_type"));
    getInstance().setLogType(log);

    auto output = dom::VariableStorage::touchWord("log_output"s);
    getInstance().setOutputType(output);
}

std::string
gen::Log::applyCommand(const route::Command& aCommand) noexcept
{
    return getInstance().applyCommandNonstatic(aCommand);
}

//--------------------------------------------------------------------------------

std::string
gen::Log::applyCommandNonstatic(const route::Command& aCommand) noexcept
{

    auto logIt = aCommand.variables.find("type");
    if (logIt != aCommand.variables.end())
    {
        setLogType(logIt->second);
    }

    auto outIt = aCommand.variables.find("output");
    if (outIt != aCommand.variables.end())
    {
        setOutputType(outIt->second);
    }

    return "TODO: result";
}

void
gen::Log::setLogType(const std::string& aLogType) noexcept
{
    static std::unordered_map<std::string, PrintStatus> statusMap = {
        {"info",    PrintStatus::Info   },
        {"warning", PrintStatus::Warning},
        {"error",   PrintStatus::Error  }
    };

    auto it = statusMap.find(aLogType);
    if (aLogType.empty())
    {
        it = statusMap.find("info");
        writeWarning("No log setting, default setting applied (info)");
    }

    if (it != statusMap.end())
    {
        mStatus = it->second;
        writeInfo("Log setting changed (", it->first, ")");
    }
    else
    {
        writeError("No such log setting (", aLogType, ")");
    }
}

void
gen::Log::setOutputType(const std::string& aOutputType) noexcept
{
    clear();
    if (aOutputType == "cout")
    {
        mIsFileOutput = false;
        mStreams      = &std::cout;

        writeInfo("Log buffer changed to stdout");
    }
    else if (aOutputType == "cerr")
    {
        mIsFileOutput = false;
        mStreams      = &std::cerr;

        writeInfo("Log buffer changed to stderr");
    }
    else if (!aOutputType.empty())
    {
        mIsFileOutput = true;
        mStreams      = new std::ofstream(aOutputType);

        writeInfo("Log buffer changed to ", aOutputType, " file");
    }
    else
    {
        mIsFileOutput = false;
        mStreams      = &std::cout;

        writeWarning("No log buffer, default setting applied (cout)");
    }
}

//--------------------------------------------------------------------------------

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
//         ** (because we don't yet know how long the message string will
//         be).
//         */
//         size_t size = FormatMessageA(
//             FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
//                 FORMAT_MESSAGE_IGNORE_INSERTS,
//             NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL,
//             SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

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
