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
    static str::String toHTMLHref(const char* aData,
                                  const char* aName = "Файлик") noexcept;
    static str::String toHTMLSrc(const char* aStr) noexcept;

    static str::String toSite(const char* aStr) noexcept;

private:
    str::String mUrl;

    UrlWrapper() noexcept;
    static UrlWrapper& getInstance() noexcept;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !HTML_WRAPPER_HPP
