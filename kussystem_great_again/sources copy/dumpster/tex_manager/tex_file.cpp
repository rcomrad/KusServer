#include "tex_file.hpp"

#include "domain/date_and_time.hpp"

#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"

#include "tex_table.hpp"

tex::TexFile::TexFile() noexcept
{
    mData +=
        file::File::getAllData(core::Path::getPathUnsafe("header.textemp"));
}

str::String
tex::TexFile::printToFile() noexcept
{
    mData += "\\end{document}\n";
    str::String name = dom::DateAndTime::getCurentTimeSafe() + ".tex";
    return file::File::writeData("print", name, mData).value();
}

void
tex::TexFile::addFile(const char* aFileName) noexcept
{
    auto curFile = file::File::getLines(core::Path::getPathUnsafe(aFileName));

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

str::String
tex::TexFile::makeFromFIle(const char* aFileName) noexcept
{
    mData += " \\begin{document}\n";

    auto templ = file::File::getLines(core::Path::getPathUnsafe(aFileName));

    for (auto& i : templ)
    {
        if (i == "-")
        {
            mData += "\\clearpage\n";
        }
        else if (i[0] == '*')
        {
            auto blocks = file::Parser::slice(i, ";");
            int cnt     = std::stoi(blocks[1]);
            auto files  = file::Parser::slice(blocks[2], ",");
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
            auto blocks = file::Parser::slice(i, ";");
            auto files  = file::Parser::slice(blocks[2], ",");
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
