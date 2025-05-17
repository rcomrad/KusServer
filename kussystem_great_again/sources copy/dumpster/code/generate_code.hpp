#ifndef GENERATE_CODE_HPP
#define GENERATE_CODE_HPP

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "code_file.hpp"

namespace code
{
class CodeGenerator
{
public:
    CodeGenerator() noexcept;

    void makeAll() noexcept;

    void makeDatabaseStructure() noexcept;
    // void generateDatabaseStructuresHPPFile() noexcept;
    // void generateDatabaseStructuresCPPFile() noexcept;

    void makePostHandler() noexcept;
    void makeGetRouter() noexcept;

    void generate(
        CodeFile::FileType aType = CodeFile::FileType::ALL) const noexcept;

private:
    std::map<str::String, std::vector<std::array<str::String, 2>>> mTables;

    std::vector<CodeFile> mFiles;

    void getTableData() noexcept;

    void addRouter(
        code::CodeClass& aClass,
        const char* aName,
        std::unordered_map<str::String, str::String> aNameMap) const noexcept;

    std::array<str::String, 2> makeRouterFunction(
        const std::unordered_map<str::String, str::String>& aNameMap,
        str::String aPostfix = "") const noexcept;
};

} // namespace code

#endif // !GENERATE_CODE_HPP
