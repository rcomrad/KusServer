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
    static str::String toHTMLHref(const str::String& aData,
                                  const str::String& aName = "Файлик") noexcept;
    static str::String toHTMLSrc(const str::String& aStr) noexcept;

    static str::String toSite(const str::String& aStr) noexcept;

private:
    str::String mUrl;

    UrlWrapper() noexcept;
    static UrlWrapper& getInstance() noexcept;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !HTML_WRAPPER_HPP
