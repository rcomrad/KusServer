#include <string.h>
#include <string>

#define __FILENAME__ \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define __FOLDERNAME_CHR__ util::getSourceFolderNameChr(__FILE__)
#define __FOLDERNAME_STR__ util::getSourceFolderNameStr(__FILE__)

namespace util
{
const char*
getSourceFolderNameChr(const char* a_file_path) noexcept;
const std::string&
getSourceFolderNameStr(const char* a_file_path) noexcept;
} // namespace util
