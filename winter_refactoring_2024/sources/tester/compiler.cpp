#include "compiler.hpp"

//--------------------------------------------------------------------------------

#include <fstream>

#include "general_tools/log.hpp"

#include "text_data/path.hpp"
#include "process/process.hpp"

//--------------------------------------------------------------------------------

std::string test::Compiler::mCPPCompiler =
    text::Path::getPathUnsafe("compiler") + "magicCPPCompiler.cmd";

std::unordered_map<std::string, test::Compiler::Language>
    test::Compiler::mLanguages = {
        {"cpp", test::Compiler::Language::CPP       },
        {"py",  test::Compiler::Language::PYTHON    },
        {"p",   test::Compiler::Language::PASCAL_XXA},
        {"pas", test::Compiler::Language::PASCAL_XXA}
};

//--------------------------------------------------------------------------------

std::vector<std::string>
test::Compiler::getExecutableCommand(
    const std::string& aFileName, const std::string& aOutputFileName) noexcept
{
    int num = aFileName.size() - 1;
    while (num >= 1 && aFileName[num] != '.') num--;
    std::string extension = aFileName.substr(num + 1);

    std::vector<std::string> result;

    auto it = mLanguages.find(extension);
    if (it != mLanguages.end())
    {
        switch (it->second)
        {
            case Language::CPP:
                result = prepareCommandForCPP(aFileName, aOutputFileName);
                break;

            case Language::PYTHON:
                result = prepareCommandForPython(aFileName);
                break;

            case Language::PASCAL_XXA:
                result = prepareCommandForPython(aFileName);
                break;
        }
    }

    return result;
}

//--------------------------------------------------------------------------------

std::vector<std::string>
test::Compiler::prepareCommandForCPP(
    const std::string& aFileName, const std::string& aOutputFileName) noexcept
{
    std::vector<std::string> compileCommand;

    auto outputName = aOutputFileName + ".exe";
#ifdef BILL_WINDOWS
    compileCommand.emplace_back(mCPPCompiler);
    compileCommand.emplace_back(aFileName);
    compileCommand.emplace_back(outputName);
#else
    compileCommand.emplace_back("g++");
    compileCommand.emplace_back("-std=c++2a");
    compileCommand.emplace_back(aFileName);
    compileCommand.emplace_back("-o");
    compileCommand.emplace_back(outputName);
#endif

    proc::Process compiler;
    compiler.setComand(compileCommand);
    compiler.create();

    std::vector<std::string> result;

    // TODO: do i need double args
    // return {outputName, outputName};
    bool flag = compiler.run();
    std::ifstream exe(outputName, std::ios::binary);
    flag &= exe.is_open();
    exe.close();
    if (flag)
    {
        result = {outputName};
    }

    return result;
}

//--------------------------------------------------------------------------------

std::vector<std::string>
test::Compiler::prepareCommandForPython(const std::string& aFileName) noexcept
{
    std::vector<std::string> result;
    result.emplace_back("python3");
    result.emplace_back(aFileName);
    return result;
}

std::vector<std::string>
test::Compiler::prepareCommandForPascal(const std::string& aFileName) noexcept
{
    std::string temp;
    temp = aFileName;
    while (temp.back() != '.') temp.pop_back();
    temp.pop_back();

    std::vector<std::string> compileCommand;
    compileCommand.emplace_back("pc");
    compileCommand.emplace_back(aFileName);

    proc::Process compiler;
    compiler.setComand(compileCommand);
    compiler.create();

    std::vector<std::string> result;
    if (compiler.run()) result = {temp};
    return result;
}

//--------------------------------------------------------------------------------
