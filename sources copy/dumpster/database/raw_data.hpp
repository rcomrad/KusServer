
#ifndef RAW_DATA_HPP
#define RAW_DATA_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <vector>

//--------------------------------------------------------------------------------

namespace data
{

struct RawData
{
    std::unordered_map<std::string, std::string> header;
    std::vector<std::vector<std::string>> value;
    std::vector<std::vector<std::string>> additionalInfo;
};
using RawDataArray = std::unordered_map<std::string, RawData>;

} // namespace data

//--------------------------------------------------------------------------------

#endif // !RAW_DATA_HPP
