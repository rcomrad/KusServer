#ifndef LOG_HPP
#define LOG_HPP

#include <ostream>
#include <vector>

#include "text_data/to_string.hpp"

#include "router/command.hpp"
#include "router/router_node.hpp"

namespace gen
{

class Log
{
public:
    static void reloadFromSettings() noexcept;
    static std::string applyCommand(const route::Command& aCommand) noexcept;

    //--------------------------------------------------------------------------------

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

    //--------------------------------------------------------------------------------

private:
    static route::RouterNode mNode;

    enum class PrintStatus
    {
        Nun,
        Info,
        Warning,
        Error
    };
    bool mIsFileOutput;
    PrintStatus mStatus;
    std::ostream* mStreams;

    //--------------------------------------------------------------------------------

    Log() noexcept;
    ~Log();
    void clear() noexcept;
    static Log& getInstance() noexcept;

    //--------------------------------------------------------------------------------

    std::string applyCommandNonstatic(const route::Command& aCommand) noexcept;
    void setLogType(const std::string& aLogType) noexcept;
    void setOutputType(const std::string& aOutputType) noexcept;

    //--------------------------------------------------------------------------------

    template <typename... Args>
    void write(Args&&... args) noexcept
    {
        std::string str;
        std::vector<std::string> temp;

        (void)(temp.emplace_back(text::toString(std::forward<Args>(args)), 0), ...);
        // (void)(temp.emplace_back(toString      (std::forward<Args>(args)), 0), ...);
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

    //--------------------------------------------------------------------------------

    template <typename... Args>
    void writeInfoNonstatic(Args&&... args) noexcept
    {
        if (mStatus == PrintStatus::Info)
        {
            write("Info: ", std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void writeWarningNonstatic(Args&&... args) noexcept
    {
        if (mStatus <= PrintStatus::Warning)
        {
            write("->Warning: ", std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void writeErrorNonstatic(Args&&... args) noexcept
    {
        if (mStatus <= PrintStatus::Error)
        {
            write("!--->ERROR: ", std::forward<Args>(args)...);
        }
    }

    //--------------------------------------------------------------------------------
};

// clang-format off
#define LOG_INFO(...)     gen::Log::writeInfo    (__FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_WARNING(...)  gen::Log::writeWarning (__FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_ERROR(...)    gen::Log::writeError   (__FILE__, __LINE__, __func__, __VA_ARGS__)
// clang-format on

} // namespace gen

#endif // !LOG_HPP
