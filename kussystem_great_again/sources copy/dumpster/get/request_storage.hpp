#ifndef REQUEST_STORAGE_HPP
#define REQUEST_STORAGE_HPP

#include <string>
#include <unordered_map>

#include "get/request_parser.hpp"

namespace get
{
class RequestStorage
{
public:
    static RequestParser::DataRequest& getRequest(
        const char* aRequest) noexcept;

private:
    std::unordered_map<str::String, RequestParser::DataRequest> mStorage;

    RequestStorage() noexcept = default;
    static RequestStorage& getInstance() noexcept;
};

}; // namespace get

#endif // !REQUEST_STORAGE_HPP
