#ifndef FILE_DATA_HPP
#define FILE_DATA_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace file
{

class FileData
{
private:
    struct TableData
    {
        std::string name;
        std::vector<std::vector<std::string>> value;
        std::vector<std::string> additionalInfo;
    };

public:
    std::unordered_map<std::string, TableData> data;

    auto begin() noexcept
    {
        return data.begin();
    }
    auto end() noexcept
    {
        return data.end();
    }

    auto cbegin() noexcept
    {
        return data.cbegin();
    }
    auto cend() noexcept
    {
        return data.cend();
    }
};

} // namespace file

#endif //! FILE_DATA_HPP
