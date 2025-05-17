#include "url_wrapper.hpp"

#include "text_data/file.hpp"

#include "general_tools/log.hpp"

dom::UrlWrapper&
dom::UrlWrapper::getInstance() noexcept
{
    static UrlWrapper instance;
    return instance;
}

//--------------------------------------------------------------------------------

std::string
dom::UrlWrapper::toHTMLHref(const std::string& aData,
                            const std::string& aName) noexcept
{
    return " <a href=\"" + getInstance().mUrl + aData + "\"/>" + aName +
           "</a> <br>";
}

std::string
dom::UrlWrapper::toHTMLSrc(const std::string& aStr) noexcept
{
    return " <img src=\"" + getInstance().mUrl + aStr + "\"/><br>";
}

std::string
dom::UrlWrapper::toSite(const std::string& aStr) noexcept
{
    return getInstance().mUrl + aStr;
}

//--------------------------------------------------------------------------------

dom::UrlWrapper::UrlWrapper() noexcept
{
    auto temp = text::File::getWords("config", "url.pass");
    if (temp.size() > 0 && temp[0].size() > 0)
    {
        mUrl = "https://" + temp[0][0] + "/";
    }
    else
    {
        LOG_ERROR("Can't read site url!"s);
    }
}
