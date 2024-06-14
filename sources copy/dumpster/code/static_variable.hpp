#ifndef STATIC_VARIABLE_HPP
#define STATIC_VARIABLE_HPP

#include <fstream>
#include <string>

namespace code
{
class StaticVariable
{
public:
    void setNamespace(const str::String& aNamespace) noexcept;
    void setClass(const str::String& aClass) noexcept;

    void setType(const str::String& aType) noexcept;
    void setName(const str::String& aName) noexcept;
    void setInitialisation(const str::String& aInitialisation) noexcept;

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
