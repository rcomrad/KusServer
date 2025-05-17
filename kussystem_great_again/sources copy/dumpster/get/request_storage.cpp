#include "request_storage.hpp"

get::RequestParser::DataRequest&
get::RequestStorage::getRequest(const char* aRequest) noexcept
{
    auto& instance = getInstance();

    auto it = instance.mStorage.find(aRequest);
    if (it == instance.mStorage.end())
    {
        it = instance.mStorage
                 .insert({aRequest, get::RequestParser::process(aRequest)})
                 .first;
    }

    return it->second;
}

get::RequestStorage&
get::RequestStorage::getInstance() noexcept
{
    static RequestStorage instance;
    return instance;
}
