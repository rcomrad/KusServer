#ifndef KUS_FILE_HPP
#define KUS_FILE_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <vector>

#include "file_data.hpp"

//--------------------------------------------------------------------------------

namespace file
{

class File
{
public:
    static FileData dmpParser(std::string aFileName) noexcept;

};

} // namespace file

//--------------------------------------------------------------------------------

#endif // !KUS_FILE_HPP
