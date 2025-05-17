#include "file_router.hpp"

#include "text_data/file.hpp"
#include "text_data/parser.hpp"

#include "post/post_router.hpp"

std::unordered_map<std::string, decltype(&core::FileRouter::dmpParser)>
    core::FileRouter::mRouter = {
        {"dmp",  &core::FileRouter::dmpParser },
        {"data", &core::FileRouter::dataParser},
        {"csv",  &core::FileRouter::csvParser }
};

data::RawDataArray
core::FileRouter::process(const std::string& aFileName) noexcept
{
    auto extension = text::Parser::getFileExtension(aFileName);
    auto it        = mRouter.find(extension);
    data::RawDataArray result;
    if (it != mRouter.end()) result = it->second(aFileName);
    return result;
}

data::RawDataArray
core::FileRouter::dmpParser(const std::string& aFileName) noexcept
{
    auto words = text::File::getWords(aFileName, text::FileType::File,
                                      &core::FileRouter::isDMPSeparator);
    data::RawDataArray res;
    for (size_t i = 0; i < words.size(); ++i)
    {
        if (words[i].empty()) continue;
        auto& curArray = res[words[i][0]];

        for (++i; i < words.size() && words[i].size() && words[i][0] != "END";
             ++i)
        {
            curArray.value.emplace_back(std::move(words[i]));
        }
    }
    return res;
}

data::RawDataArray
core::FileRouter::dataParser(const std::string& aFileName) noexcept
{
    auto words = text::File::getWords(aFileName);
    data::RawDataArray res;
    for (size_t i = 0; i < words.size(); ++i)
    {
        if (words[i].empty()) continue;
        auto& curArray      = res[words[i][0]];
        int additionalLines = std::stoi(words[i][1]);

        for (i += 2;
             i < words.size() && words[i].size() && words[i][0] != "END"; ++i)
        {
            curArray.value.emplace_back(std::move(words[i]));
            for (int j = 0; j < additionalLines; ++j)
            {
                curArray.additionalInfo.emplace_back(std::move(words[++i]));
            }
        }
    }
    return res;
}

data::RawDataArray
core::FileRouter::csvParser(const std::string& aFileName) noexcept
{
    auto words = text::File::getWords(aFileName, text::FileType::File,
                                      &core::FileRouter::isCSVSeparator);
    data::RawDataArray res;
    auto& curArray = res["data"];
    words[0].clear();
    for (auto& i : words)
    {
        if (i.empty()) continue;
        curArray.value.emplace_back(std::move(i));
    }
    return res;
}

bool
core::FileRouter::isSeparator(char c) noexcept
{
    return c == '\t' || c == ' ' || c == ';' || c == '\0';
}

bool
core::FileRouter::isDMPSeparator(char c) noexcept
{
    return c == '\t' || c == ';' || c == '\0';
}

bool
core::FileRouter::isCSVSeparator(char c) noexcept
{
    return c == ';' || c == '\0';
}
