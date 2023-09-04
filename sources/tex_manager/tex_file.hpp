#ifndef TEX_FILE_HPP
#define TEX_FILE_HPP

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "domain/holy_trinity.hpp"

namespace tex
{
class TexFile
{
public:
    TexFile() noexcept;
    HOLY_TRINITY_NOCOPY(TexFile);

    // template <typename T>
    // void add(T&& aData, bool aAddNewPage = true) noexcept
    // {
    //     aData.finish();
    //     mData += aData.get();
    //     if (aAddNewPage) mData += "\\clearpage\n";
    // }

    std::string printToFile() noexcept;

    template <typename T>
    void setVariable(const std::string& aName, T&& aVariable) noexcept
    {
        mVariables[aName] = std::forward<T>(aVariable);
        std::reverse(mVariables[aName].begin(), mVariables[aName].end());
    }

    std::string makeFromFIle(const std::string& aFileName) noexcept;

private:
    std::string mData;
    std::unordered_map<std::string, std::vector<std::string>> mVariables;

    void addFile(const std::string& aFileName) noexcept;
};

}; // namespace tex

#endif // !TEX_FILE_HPP
