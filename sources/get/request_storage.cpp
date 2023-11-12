#include "request_storage.hpp"

#include <utility>

#include "domain/log.hpp"

using namespace std::chrono_literals;

bool get::RequestStorage::mMutexFlag = false;
std::mutex get::RequestStorage::mInsertMutex;

get::RequestParser::DataRequest&
get::RequestStorage::getRequest(const std::string& aRequest) noexcept
{
    static auto& instance = getInstance();
    while (mMutexFlag)
        ;

    auto it = instance.mStorage.find(aRequest);
    if (it == instance.mStorage.end())
    {
        mInsertMutex.lock();
        mMutexFlag = true;
        std::this_thread::sleep_for(200ms);

        it = instance.mStorage
                 .insert({aRequest, get::RequestParser::process(aRequest)})
                 .first;
        dom::writeInfo("Adding request to storage:", aRequest);

        mMutexFlag = false;
        mInsertMutex.unlock();
    }

    return it->second;
}

get::RequestStorage&
get::RequestStorage::getInstance() noexcept
{
    static RequestStorage instance;
    return instance;
}
