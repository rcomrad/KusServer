#include "compiler.hpp"

//--------------------------------------------------------------------------------

#include <fstream>

#include "domain/log.hpp"

#include "file_data/path.hpp"
#include "process/process.hpp"

//--------------------------------------------------------------------------------

str::String test::Compiler::mCPPCompiler =
    core::Path::getPathUnsafe("compiler") + "magicCPPCompiler.cmd";

std::unordered_map<str::String, test::Compiler::Language>
    test::Compiler::mLanguages = {
        {"cpp", test::Compiler::Language::CPP       },
        {"py",  test::Compiler::Language::PYTHON    },
        {"p",   test::Compiler::Language::PASCAL_XXA},
        {"pas", test::Compiler::Language::PASCAL_XXA}
};

//--------------------------------------------------------------------------------

std::vector<str::String>
test::Compiler::getExecutableCommand(const char* aFileName,
                                     const char* aOutputFileName) noexcept
{
    int num = aFileName.size() - 1;
    while (num >= 1 && aFileName[num] != '.') num--;
    str::String extension = aFileName.substr(num + 1);

    std::vector<str::String> result;

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

std::vector<str::String>
test::Compiler::prepareCommandForCPP(const char* aFileName,
                                     const char* aOutputFileName) noexcept
{
    std::vector<str::String> compileCommand;

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

    std::vector<str::String> result;

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

std::vector<str::String>
test::Compiler::prepareCommandForPython(const char* aFileName) noexcept
{
    std::vector<str::String> result;
    result.emplace_back("python3");
    result.emplace_back(aFileName);
    return result;
}

std::vector<str::String>
test::Compiler::prepareCommandForPascal(const char* aFileName) noexcept
{
    str::String temp;
    temp = aFileName;
    while (temp.back() != '.') temp.pop_back();
    temp.pop_back();

    std::vector<str::String> compileCommand;
    compileCommand.emplace_back("pc");
    compileCommand.emplace_back(aFileName);

    proc::Process compiler;
    compiler.setComand(compileCommand);
    compiler.create();

    std::vector<str::String> result;
    if (compiler.run()) result = {temp};
    return result;
}

//--------------------------------------------------------------------------------
