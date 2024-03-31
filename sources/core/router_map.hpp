#ifndef ROUTER_MASTER_HPP
#define ROUTER_MASTER_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "domain/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace route
{
class CallBackStorage
{
public:
    static void add(const str::string& aVolumeName,
                    const str::string& aNodeName,
                    void* aFunc) noexcept;

    static void* get(const str::string& aVolumeName,
                     const str::string& aNodeName) noexcept;

private:
    HOLY_TRINITY_SINGLE(CallBackStorage);
    
    static CallBackStorage& getInstance() noexcept;

    //----------------------------------------------------------------------------

    void addNonstatic(const str::string& aVolumeName,
                      const str::string& aNodeName,
                      void* aFunc) noexcept;

    void* getNonstatic(const str::string& aVolumeName,
                       const str::string& aNodeName) const noexcept;

    //----------------------------------------------------------------------------

    std::unordered_map<str::string, std::unordered_map<str::string, void*>>
        mMap;
};
} // namespace route

//--------------------------------------------------------------------------------

#endif // !ROUTER_MASTER_HPP
