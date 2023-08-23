#ifndef FILE_ROUTER_HPP
#define FILE_ROUTER_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "database/raw_data.hpp"

namespace core
{

class FileRouter
{
public:
    static data::RawDataArray process(const std::string& aFileName) noexcept;

private:
    static data::RawDataArray dmpParser(const std::string& aFileName) noexcept;
    static data::RawDataArray dataParser(const std::string& aFileName) noexcept;
    static data::RawDataArray csvParser(const std::string& aFileName) noexcept;

    static std::unordered_map<std::string, decltype(&dmpParser)> mRouter;

    static bool isSeparator(char c) noexcept;
    static bool isDMPSeparator(char c) noexcept;
    static bool isCSVSeparator(char c) noexcept;
};

} // namespace core

#endif // !FILE_ROUTER_HPP
