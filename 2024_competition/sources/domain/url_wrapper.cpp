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
        dom::writeError("Can't read site url!"s);
    }
}

dom::UrlWrapper&
dom::UrlWrapper::getInstance() noexcept
{
    static UrlWrapper instance;
    return instance;
}

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
dom::UrlWrapper::toHTMLAudio(const std::string& aStr) noexcept
{
    return " <audio controls> <source src=\"" + getInstance().mUrl + aStr +
           "\"  type=\"audio/mp3\"/> </audio> <br>";
}

std::string
dom::UrlWrapper::toSite(const std::string& aStr) noexcept
{
    return getInstance().mUrl + aStr;
}
