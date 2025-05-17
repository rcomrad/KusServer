#include "url_wrapper.hpp"

#include "domain/log.hpp"

#include "file_data/file.hpp"

dom::UrlWrapper::UrlWrapper() noexcept
{
    auto temp = file::File::getWords("config", "url.pass");
    if (temp.size() > 0 && temp[0].size() > 0)
    {
        mUrl = "https://" + temp[0][0] + "/";
    }
    else
    {
        LOG_ERROR("Can't read site url!"s);
    }
}

dom::UrlWrapper&
dom::UrlWrapper::getInstance() noexcept
{
    static UrlWrapper instance;
    return instance;
}

str::String
dom::UrlWrapper::toHTMLHref(const char* aData, const char* aName) noexcept
{
    return " <a href=\"" + getInstance().mUrl + aData + "\"/>" + aName +
           "</a> <br>";
}

str::String
dom::UrlWrapper::toHTMLSrc(const char* aStr) noexcept
{
    return " <img src=\"" + getInstance().mUrl + aStr + "\"/><br>";
}

str::String
dom::UrlWrapper::toSite(const char* aStr) noexcept
{
    return getInstance().mUrl + aStr;
}
