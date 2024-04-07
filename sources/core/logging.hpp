#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <ostream>
#include <vector>

#include "domain/holy_trinity.hpp"

#include "string/kus_string.hpp"
#include "string/to_string.hpp"

//------------------------------------------------------------------------------

namespace core
{

class Logging
{
public:
    enum class LogLevel
    {
        Nun,
        Info,
        Warning,
        Error
    };

    enum class OutputType
    {
        Nun,
        Cout,
        Cerr,
        File
    };

    static void setLogLevel(LogLevel aLogLevel) noexcept;
    static void setOutputType(OutputType aOutputType,
                              const str::string& aFileName = "") noexcept;

    //--------------------------------------------------------------------------

    template <typename... Args>
    static void writeInfo(Args&&... args) noexcept
    {
        getInstance().writeInfoNonstatic(std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void writeWarning(Args&&... args) noexcept
    {
        getInstance().writeWarningNonstatic(std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void writeError(Args&&... args) noexcept
    {
        getInstance().writeErrorNonstatic(std::forward<Args>(args)...);
    }

private:
    bool mIsFileOutput;
    LogLevel mLogLevel;
    std::ostream* mStreams;

    //--------------------------------------------------------------------------

    HOLY_TRINITY_SINGLE(Logging);
    Logging() noexcept;
    ~Logging();
    void clear() noexcept;
    static Logging& getInstance() noexcept;

    //--------------------------------------------------------------------------

    void setOutputTypeNonstatic(OutputType aOutputType,
                                const str::string& aFileName) noexcept;

    //--------------------------------------------------------------------------

    template <typename... Args>
    void writeInfoNonstatic(Args&&... args) noexcept
    {
        if (mLogLevel == LogLevel::Info)
        {
            write("Info: ", std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void writeWarningNonstatic(Args&&... args) noexcept
    {
        if (mLogLevel <= LogLevel::Warning)
        {
            write("-->Warning: ", std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void writeErrorNonstatic(Args&&... args) noexcept
    {
        if (mLogLevel <= LogLevel::Error)
        {
            write("!--->ERROR: ", std::forward<Args>(args)...);
        }
    }

    //--------------------------------------------------------------------------

    template <typename... Args>
    void write(Args&&... args) noexcept
    {
        str::string str;
        std::vector<str::string> temp;

        (void)(temp.emplace_back(str::toString(std::forward<Args>(args)), 0),
               ...);
        // (void)(temp.emplace_back(toString      (std::forward<Args>(args)),
        // 0), ...);
        for (int i = 0; i < temp.size() - 1; ++i)
        {
            if (!temp[i + 1].empty() && temp[i].back() != '(' &&
                temp[i + 1].front() != ')' && temp[i].back() != '\'' &&
                temp[i + 1].front() != '\'')
            {
                temp[i] += ' ';
            }
        }
        for (auto&& i : temp)
        {
            str += std::move(i);
        }

        str += ".\n";

        (*mStreams) << str;
        (*mStreams).flush();
    }

    //--------------------------------------------------------------------------
};

// clang-format off
#define LOG_INFO(...)     core::Logging::writeInfo    (__FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_WARNING(...)  core::Logging::writeWarning (__FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_ERROR(...)    core::Logging::writeError   (__FILE__, __LINE__, __func__, __VA_ARGS__)
// clang-format on

} // namespace core

#endif // !LOGGING_HPP
