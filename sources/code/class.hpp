#ifndef CLASS_HPP
#define CLASS_HPP

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "function.hpp"
#include "static_variable.hpp"

namespace code
{

class Class
{
    // enum class RouterType
    // {
    //     VALUE,
    //     FUNCTION,
    //     VARIADIC
    // };

public:
    void setName(const std::string& aName) noexcept;
    void setNamespace(const std::string& aNamespace) noexcept;

    void addRouterFunction(const std::string& aName,
                           const std::string& aType,
                           const std::string& aBody) noexcept;
    void addFuncRouterForDatabase(const std::string& aName,
                                  const std::string& aFunction,
                                  const std::string& aBody) noexcept;

private:
    static std::unordered_map<std::string, std::string> globalPaths;

    std::string mName;
    std::string mNamespace;
    std::string mFileName;
    std::string mFilePath;

    std::vector<Function> mFunctions;
    std::vector<StaticVariable> mStaticVariables;

    std::vector<std::string> mDatabase;

    void reloadName() noexcept;
};

} // namespace code

#endif // !CLASS_HPP
