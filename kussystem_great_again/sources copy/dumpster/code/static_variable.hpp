#ifndef STATIC_VARIABLE_HPP
#define STATIC_VARIABLE_HPP

#include <fstream>
#include <string>

namespace code
{
class StaticVariable
{
public:
    void setNamespace(const char* aNamespace) noexcept;
    void setClass(const char* aClass) noexcept;

    void setType(const char* aType) noexcept;
    void setName(const char* aName) noexcept;
    void setInitialisation(const char* aInitialisation) noexcept;

    void outputToHpp(std::ofstream& aOut) const noexcept;
    void outputToCpp(std::ofstream& aOut) const noexcept;

private:
    str::String mNamespace;
    str::String mClass;

    str::String mType;
    str::String mName;
    str::String mInitialisation;
};

} // namespace code

#endif // !STATIC_VARIABLE_HPP
