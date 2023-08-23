#ifndef LOG_HPP
#define LOG_HPP

#include <ostream>
#include <vector>

#include "to_string.hpp"

namespace dom
{

class Log
{
public:
    static Log& getInstance() noexcept;

    void reloadSettings() noexcept;

    template <typename... Args>
    void writeInfo(Args&&... args) noexcept
    {
        if (mStatus == PrintStatus::Info)
        {
            write("Info: ", std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void writeWarning(Args&&... args) noexcept
    {
        if (mStatus <= PrintStatus::Warning)
        {
            write("->Warning: ", std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void writeError(Args&&... args) noexcept
    {
        if (mStatus <= PrintStatus::Error)
        {
            write("!--->ERROR: ", std::forward<Args>(args)...);
        }
    }

private:
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

    Log() noexcept;
    ~Log();

    template <typename... Args>
    void write(Args&&... args) noexcept
    {
        std::string str;
        std::vector<std::string> temp;

        (void)(temp.emplace_back(toString(std::forward<Args>(args)), 0), ...);
        for (int i = 0; i < temp.size() - 1; ++i)
        {
            if (temp[i].back() != '(' && temp[i + 1].front() != ')' &&
                temp[i].back() != '\'' && temp[i + 1].front() != '\'')
            {
                temp[i] += ' ';
            }
        }
        for (auto&& i : temp)
        {
            str += std::move(i);
        }
        // ((void)(str += toString(std::forward<Args>(args)) + " ", 0), ...);

        str += ".\n";

        (*mStreams) << str;
        (*mStreams).flush();
    }
};

template <typename... Args>
void
writeInfo(Args&&... args) noexcept
{
    dom::Log::getInstance().writeInfo(std::forward<Args>(args)...);
}

template <typename... Args>
void
writeWarning(Args&&... args) noexcept
{
    dom::Log::getInstance().writeWarning(std::forward<Args>(args)...);
}

template <typename... Args>
void
writeError(Args&&... args) noexcept
{
    dom::Log::getInstance().writeError(std::forward<Args>(args)...);
}

} // namespace dom
#endif // !LOG_HPP
