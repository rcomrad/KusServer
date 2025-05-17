#ifndef REQUEST_STORAGE_HPP
#define REQUEST_STORAGE_HPP

#include <mutex>
#include <string>
#include <unordered_map>

#include "get/request_parser.hpp"

namespace get
{
class RequestStorage
{
public:
    static RequestParser::DataRequest& getRequest(
        const std::string& aRequest) noexcept;

private:
    static bool mMutexFlag;
    static std::mutex mInsertMutex;
    std::unordered_map<std::string, RequestParser::DataRequest> mStorage;

    RequestStorage() noexcept = default;
    static RequestStorage& getInstance() noexcept;
};

}; // namespace get

#endif // !REQUEST_STORAGE_HPP
