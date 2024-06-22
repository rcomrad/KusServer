#ifndef CODE_FUNCTION_HPP
#define CODE_FUNCTION_HPP

#include <fstream>
#include <string>

namespace code
{
class CodeFunction
{
public:
    CodeFunction(const std::string& aName = "foo") noexcept;

    void setNamespace(const std::string& aNamespace) noexcept;
    void setClass(const std::string& aClass) noexcept;

    void makeStatic() noexcept;
    void makeFunctor() noexcept;
    void makeVariadic() noexcept;

    void setTemplate(const std::string& aTemplate) noexcept;
    void setReturnType(const std::string& aType) noexcept;
    void setName(const std::string& aName) noexcept;
    void setArguments(const std::string& aArguments) noexcept;
    void setBody(const std::string& aBody) noexcept;

    void outputToHpp(std::ofstream& aOut) const noexcept;
    void outputToCpp(std::ofstream& aOut) const noexcept;

    void makeRouter(std::string aMapName) noexcept;

private:
    bool mIsStatic;
    bool mIsFunctor;
    bool mIsVariadic;

    std::string mNamespace;
    std::string mClass;

    std::string mTemplate;
    std::string mType;
    std::string mName;
    std::string mArguments;
    std::string mBody;
    std::string mMapName;

    std::string generateRouterBody() const noexcept;

    bool isTemplate() const noexcept;
};

} // namespace code

#endif // !CODE_FUNCTION_HPP
