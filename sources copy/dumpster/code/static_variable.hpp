#ifndef STATIC_VARIABLE_HPP
#define STATIC_VARIABLE_HPP

#include <fstream>
#include <string>

namespace code
{
class StaticVariable
{
public:
    void setNamespace(const std::string& aNamespace) noexcept;
    void setClass(const std::string& aClass) noexcept;

    void setType(const std::string& aType) noexcept;
    void setName(const std::string& aName) noexcept;
    void setInitialisation(const std::string& aInitialisation) noexcept;

    void outputToHpp(std::ofstream& aOut) const noexcept;
    void outputToCpp(std::ofstream& aOut) const noexcept;

private:
    std::string mNamespace;
    std::string mClass;

    std::string mType;
    std::string mName;
    std::string mInitialisation;
};

} // namespace code

#endif // !STATIC_VARIABLE_HPP
