#ifndef POPULATE_HPP
#define POPULATE_HPP

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

namespace core
{
class Populate
{
public:
    static void checkForCommands() noexcept;

private:
    static void remakeDatabase() noexcept;
    static void populate() noexcept;

    static void createDatabaseFromFile(std::string aFileName) noexcept;
    static void createEnvironment() noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !POPULATE_HPP
