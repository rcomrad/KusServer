#ifndef HTML_WRAPPER_HPP
#define HTML_WRAPPER_HPP

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

namespace dom
{
class UrlWrapper
{
public:
    static std::string toHTMLHref(const std::string& aData,
                                  const std::string& aName = "Файлик") noexcept;
    static std::string toHTMLSrc(const std::string& aStr) noexcept;
    static std::string toHTMLAudio(const std::string& aStr) noexcept;

    static std::string toSite(const std::string& aStr) noexcept;

private:
    std::string mUrl;

    UrlWrapper() noexcept;
    static UrlWrapper& getInstance() noexcept;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !HTML_WRAPPER_HPP
