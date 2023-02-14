#ifndef ASTERISK_HENDLER_HPP
#define ASTERISK_HENDLER_HPP

#include <string>
#include <unordered_map>
#include <vector>

struct AsteriskHendler
{
    static std::unordered_map<std::string_view, std::vector<std::string>> table;
};

#endif // !ASTERISK_HENDLER_HPP
