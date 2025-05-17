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

    str::String printToFile() noexcept;

    template <typename T>
    void setVariable(const char* aName, T&& aVariable) noexcept
    {
        mVariables[aName] = std::forward<T>(aVariable);
        std::reverse(mVariables[aName].begin(), mVariables[aName].end());
    }

    str::String makeFromFIle(const char* aFileName) noexcept;

private:
    str::String mData;
    std::unordered_map<str::String, std::vector<str::String>> mVariables;

    void addFile(const char* aFileName) noexcept;
};

}; // namespace tex

#endif // !TEX_FILE_HPP
