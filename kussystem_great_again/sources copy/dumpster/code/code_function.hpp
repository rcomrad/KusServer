#ifndef CODE_FUNCTION_HPP
#define CODE_FUNCTION_HPP

#include <fstream>
#include <string>

namespace code
{
class CodeFunction
{
public:
    CodeFunction(const char* aName = "foo") noexcept;

    void setNamespace(const char* aNamespace) noexcept;
    void setClass(const char* aClass) noexcept;

    void makeStatic() noexcept;
    void makeFunctor() noexcept;
    void makeVariadic() noexcept;

    void setTemplate(const char* aTemplate) noexcept;
    void setReturnType(const char* aType) noexcept;
    void setName(const char* aName) noexcept;
    void setArguments(const char* aArguments) noexcept;
    void setBody(const char* aBody) noexcept;

    void outputToHpp(std::ofstream& aOut) const noexcept;
    void outputToCpp(std::ofstream& aOut) const noexcept;

    void makeRouter(str::String aMapName) noexcept;

private:
    bool mIsStatic;
    bool mIsFunctor;
    bool mIsVariadic;

    str::String mNamespace;
    str::String mClass;

    str::String mTemplate;
    str::String mType;
    str::String mName;
    str::String mArguments;
    str::String mBody;
    str::String mMapName;

    str::String generateRouterBody() const noexcept;

    bool isTemplate() const noexcept;
};

} // namespace code

#endif // !CODE_FUNCTION_HPP
