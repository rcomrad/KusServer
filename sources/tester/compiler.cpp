#include "compiler.hpp"

//--------------------------------------------------------------------------------

#include "domain/error_message.hpp"
#include "domain/path.hpp"

#include "process/process.hpp"

//--------------------------------------------------------------------------------

std::string test::Compiler::mCPPCompiler =
    dom::Path::getPath("compiler").value() + "magicCPPCompiler.cmd";

std::unordered_map<std::string, test::Compiler::Language>
    test::Compiler::mLanguages = {
        {"cpp", test::Compiler::Language::CPP   },
        {"py",  test::Compiler::Language::PYTHON}
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
    compileCommand.emplace_back(aFileName);
    compileCommand.emplace_back("-o");
    compileCommand.emplace_back(outputName);
#endif

    proc::Process compiler;
    compiler.setComand(compileCommand);
    compiler.create();
    compiler.run();

    return {outputName, outputName};
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

//--------------------------------------------------------------------------------
