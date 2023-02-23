#ifndef DOM_PATHS_HPP
#define DOM_PATHS_HPP

//--------------------------------------------------------------------------------

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#define MAIN_PATH       dom::Path::getMainPath()
#define EXECUTABLE_PATH dom::Path::getExecutablePath()

#define RESOURCES   MAIN_PATH + "resources/"s
#define OUTPUT_PATH RESOURCES + "output/"s
#define LOGS_PATH   RESOURCES + "logs/"s
#define ERRORS_PATH WORK_DIR + "errors/"s

namespace dom
{
class Path
{
public:
    static std::optional<std::string> getPath(
        const std::string& aName) noexcept;

    static std::string getMainPath() noexcept;
    static std::string getExecutablePath() noexcept;

private:
    static std::unordered_map<std::string, std::string> mPaths;

    static std::unordered_map<std::string, std::string> getPaths() noexcept;

    static std::string getMainPathOnce() noexcept;
    static std::string getExecutablePathOnce() noexcept;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !DOM_PATHS_HPP
