#ifndef COMPILER_HPP
#define COMPILER_HPP

//--------------------------------------------------------------------------------

/*
** The compiler class manages code files for
** code execution (including code compilation).
*/

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <vector>

//--------------------------------------------------------------------------------

namespace test
{
class Compiler
{
private:
    enum class Language
    {
        NUN,
        CPP,
        PYTHON,
        PASCAL_XXA
    };

public:
    /*
    \brief Prepare a command that executes the child process and
        compiles the file in specified directory if necessary.
    \param aCode A struct with the path to code to execute,
        output directory and language information.
    */
    static std::vector<str::String> getExecutableCommand(
        const char* aFileName,
        const char* aOutputFileName) noexcept;

private:
    static std::unordered_map<str::String, Language> mLanguages;
    static str::String mCPPCompiler;

    /*
    \brief Compile the cpp file and return the cmd command to execute it.
    \param aInfo A cpp file information.
    \return An array of strings with the commands for
        exe execution execution.
    */
    static std::vector<str::String> prepareCommandForCPP(
        const char* aFileName,
        const char* aOutputFileName) noexcept;

    /*
    \brief Prepare the cmd command for python file interpretation.
    \param aInfo A python file information.
    \return An array of strings with the commands for python
        file einterpretation.
    */
    static std::vector<str::String> prepareCommandForPython(
        const char* aFileName) noexcept;

    static std::vector<str::String> prepareCommandForPascal(
        const char* aFileName) noexcept;
};
} // namespace test

//--------------------------------------------------------------------------------

#endif // !COMPILER_HPP
