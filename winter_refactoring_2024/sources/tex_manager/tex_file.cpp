#include "tex_file.hpp"

#include "domain/date_time.hpp"
#include "domain/time_handler.hpp"

#include "text_data/file.hpp"
#include "text_data/parser.hpp"
#include "text_data/path.hpp"

#include "tex_table.hpp"

tex::TexFile::TexFile() noexcept
{
    mData +=
        text::File::getAllData(text::Path::getPathUnsafe("header.textemp"));
}

std::string
tex::TexFile::printToFile() noexcept
{
    mData += "\\end{document}\n";
    std::string name =
        dom::TimeHandler::getCurentTime().getAllNoSpace() + ".tex";
    return text::File::writeData("print", name, mData).value();
}

void
tex::TexFile::addFile(const std::string& aFileName) noexcept
{
    auto curFile = text::File::getLines(text::Path::getPathUnsafe(aFileName));

    if (curFile[0] != "table")
    {
        for (auto& i : curFile)
        {
            if (i[0] == '$')
            {
                auto it = mVariables.find(i);
                i       = it->second.back();
                it->second.pop_back();
            }
            mData += i;
            mData.push_back('\n');
        }
    }
    else
    {
        tex::TexTable table(curFile, &mVariables);
        table.finish();
        mData += table.get();
        mData.push_back('\n');
    }
}

std::string
tex::TexFile::makeFromFIle(const std::string& aFileName) noexcept
{
    mData += " \\begin{document}\n";

    auto templ = text::File::getLines(text::Path::getPathUnsafe(aFileName));

    for (auto& i : templ)
    {
        if (i == "-")
        {
            mData += "\\clearpage\n";
        }
        else if (i[0] == '*')
        {
            auto blocks = text::Parser::slice(i, ";");
            int cnt     = std::stoi(blocks[1]);
            auto files  = text::Parser::slice(blocks[2], ",");
            for (int j = 0; j < cnt; ++j)
            {
                for (auto& k : files)
                {
                    if (k != "-") addFile(k);
                    else mData += "page\n";
                }
            }
        }
        else if (i[0] == '?')
        {
            auto blocks = text::Parser::slice(i, ";");
            auto files  = text::Parser::slice(blocks[2], ",");
            while (!mVariables[blocks[1]].empty())
            {
                for (auto& k : files)
                {
                    if (k != "-") addFile(k);
                    else mData += "\\clearpage\n";
                }
            }
        }
        else
        {
            addFile(i);
        }
        mData.push_back('\n');
    }
    return "";
}
