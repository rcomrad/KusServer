#ifndef ERROR_MESSAGE_HPP
#define ERROR_MESSAGE_HPP

//--------------------------------------------------------------------------------

#include <fstream>
#include <iostream>

#include "string.hpp"

//--------------------------------------------------------------------------------
/*
** This section shows all available values for
** the LOGS_OUTPUT_TYPE flag / ERRORS_OUTPUT_TYPE flag
** and what these values represent.
** -------------------------------
** LOGS_OUTPUT_TYPE values:
**
** LOGS_DEFAULT_OUTPUT     = 0
** LOGS_TO_COUT_OUTPUT     = 1
** LOGS_TO_FILE_OUTPUT     = 2
**
** DEFAULT = LOGS_TO_COUT_OUTPUT
** -------------------------------
** ERRORS_OUTPUT_TYPE values:
**
** ERRORS_DEFAULT_OUTPUT    = 0
** ERRORS_TO_COUT_OUTPUT    = 1
** ERRORS_TO_FILE_OUTPUT    = 2
** ERRORS_TO_LOG_OUTPUT     = 4
**
** DEFAULT = ERRORS_TO_COUT_OUTPUT
** -------------------------------
*/
//--------------------------------------------------------------------------------

#if LOGS_OUTPUT_TYPE == 0
#    define LOGS_DEFAULT_OUTPUT
#elif LOGS_OUTPUT_TYPE == 1
#    define LOGS_TO_COUT_OUTPUT
#elif LOGS_OUTPUT_TYPE == 2
#    define LOGS_TO_FILE_OUTPUT
#else
#    define LOG_DEFAULT_OUTPUT
#endif

//--------------------------------------------------------------------------------

#if ERRORS_OUTPUT_TYPE == 0
#    define ERRORS_DEFAULT_OUTPUT
#elif ERRORS_OUTPUT_TYPE == 1
#    define ERRORS_TO_COUT_OUTPUT
#elif ERRORS_OUTPUT_TYPE == 2
#    define ERRORS_TO_FILE_OUTPUT
#elif ERRORS_OUTPUT_TYPE == 4
#    define ERRORS_TO_LOG_OUTPUT
#else
#    define ERROR_DEFAULT_OUTPUT
#endif

//--------------------------------------------------------------------------------

namespace dom
{
class Message
{
public:
    static Message globalMessages;

    template <typename... Args> void startLogBlock(Args&&... args) noexcept
    {
        write(mLogStream, std::forward<Args>(args)...);
        ++mLogBlockCount;
    }

    template <typename... Args> void endLogBlock(Args&&... args) noexcept
    {
        write(mLogStream, std::forward<Args>(args)...);
        --mLogBlockCount;
    }

    template <typename... Args> void writeLog(Args&&... args) noexcept
    {
        write(mLogStream, std::forward<Args>(args)...);
    }

    template <typename... Args> void writeError(Args&&... args) noexcept
    {
#ifdef ERRORS_TO_LOG_OUTPUT
        write(mErrorStream, "ERROR", std::forward<Args>(args)...);
#else
        basicWrite(mErrorStream, "ERROR", std::forward<Args>(args)...);
#endif
    }

    void writeLogEndl() noexcept;

    //--------------------------------------------------------------------------------

#ifdef BILL_WINDOWS
    /*
    \brief Gets error of WinAPI.
    \return String with error messege.
    */
    std::string GetLastWinAPIError() noexcept;
#endif

private:
    std::ostream* mLogStream;
    std::ostream* mErrorStream;

    int8_t mLogBlockCount;

    //--------------------------------------------------------------------------------

    Message() noexcept;

    template <typename... Args>
    void write(std::ostream* aStream, Args&&... args) noexcept
    {
        basicWrite(aStream, std::string(mLogBlockCount, '\t'),
                   std::forward<Args>(args)...);
    }

    template <typename... Args>
    void basicWrite(std::ostream* aStream, Args&&... args) noexcept
    {
        std::string str;
        ((void)(str += toString(std::forward<Args>(args)) + " ", 0), ...);
        str += '\n';

        (*aStream) << str;
        (*aStream).flush();
    }

    template <typename S, typename = enableIfSame<S, std::string>>
    std::string toString(S&& str) noexcept
    {
        return std::forward<S>(str);
    }

    std::string toString(const char* str) noexcept
    {
        return std::string(str);
    }

    std::string toString(int64_t num) noexcept
    {
        return std::to_string(num);
    }
};
} // namespace dom

//--------------------------------------------------------------------------------

/*
ERROR FORMAT: <file or class name>, <function>,
                <approximate error number>, <error message>
*/

#ifdef _DBG_
#    define START_LOG_BLOCK(...) \
        dom::Message::globalMessages.startLogBlock(__VA_ARGS__)
#    define END_LOG_BLOCK(...) \
        dom::Message::globalMessages.endLogBlock(__VA_ARGS__)
#    define WRITE_LOG(...) dom::Message::globalMessages.writeLog(__VA_ARGS__)
#    define WRITE_LOG_ENDL(...) \
        dom::Message::globalMessages.writeLogEndl(__VA_ARGS__)
#    define WRITE_ERROR(...) \
        dom::Message::globalMessages.writeError(__VA_ARGS__)
#else
#    define START_LOG_BLOCK(...) void(0)
#    define END_LOG_BLOCK(...)   void(0)
#    define WRITE_LOG(...)       void(0)
#    define WRITE_LOG_ENDL(...)  void(0)
#    define WRITE_ERROR(...)     void(0)
#endif

//--------------------------------------------------------------------------------

#undef LOGS_OUTPUT_TYPE
#undef ERRORS_OUTPUT_TYPE

//--------------------------------------------------------------------------------

#endif // !ERROR_MESSAGE_HPP
