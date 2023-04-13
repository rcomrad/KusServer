#ifndef KUS_PATHS_HPP
#define KUS_PATHS_HPP

//--------------------------------------------------------------------------------

#include <optional>
#include <string>
#include <unordered_map>

namespace file
{
class Path
{
public:
    static Path& getInstance() noexcept;

    std::optional<std::string> getPath(const std::string& aName) noexcept;

    std::string getMainPath() noexcept;
    std::string getExecutablePath() noexcept;

private:
    Path() noexcept;

    void reset() noexcept;

    std::string getMainPathOnce() noexcept;
    std::string getExecutablePathOnce() noexcept;

    std::unordered_map<std::string, std::string> mPaths;
};
} // namespace file

//--------------------------------------------------------------------------------

#endif // !KUS_PATHS_HPP
