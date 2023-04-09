#ifndef FILE_ROUTER_HPP
#define FILE_ROUTER_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "file.hpp"
#include "file_data.hpp"

namespace file
{
    
class FileRouter
{
public:
    static void process(const std::string& aFileName) noexcept;
    static FileData getFileData(const std::string& aFileName) noexcept;

private:
    static std::unordered_map<std::string, decltype(&File::dmpParser)> mRouter;
};

} // namespace file
#endif // !FILE_ROUTER_HPP
