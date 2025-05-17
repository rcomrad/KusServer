#ifndef REQUEST_MAP_HPP
#define REQUEST_MAP_HPP

//--------------------------------------------------------------------------------

#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

//--------------------------------------------------------------------------------

namespace get
{

class RequestMap
{
public:
    static RequestMap& getInstance() noexcept;

private:
    RequestMap() = default;
};

} // namespace get

//--------------------------------------------------------------------------------

#endif // !REQUEST_MAP_HPP
