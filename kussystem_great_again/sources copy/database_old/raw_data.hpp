
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
    std::unordered_map<str::String, str::String> header;
    std::vector<std::vector<str::String>> value;
    std::vector<std::vector<str::String>> additionalInfo;
};
using RawDataArray = std::unordered_map<str::String, RawData>;

} // namespace data

//--------------------------------------------------------------------------------

#endif // !RAW_DATA_HPP
