#include "router_map.hpp"

//--------------------------------------------------------------------------------

route::CallBackStorage&
route::CallBackStorage::getInstance() noexcept
{
    static CallBackStorage instance;
    return instance;
}

//--------------------------------------------------------------------------------

void
route::CallBackStorage::add(const str::string& aVolumeName,
                      const str::string& aNodeName,
                      void* aFunc) noexcept
{
    getInstance().addNonstatic(aVolumeName, aNodeName, aFunc);
}

void*
route::CallBackStorage::get(const str::string& aVolumeName,
                      const str::string& aNodeName) noexcept
{
    return getInstance().getNonstatic(aVolumeName, aNodeName);
}

//--------------------------------------------------------------------------------

void
route::CallBackStorage::addNonstatic(const str::string& aVolumeName,
                               const str::string& aNodeName,
                               void* aFunc) noexcept
{
    mMap[aVolumeName][aNodeName] = aFunc;
}

void*
route::CallBackStorage::getNonstatic(const str::string& aVolumeName,
                               const str::string& aNodeName) const noexcept
{
    void* result = nullptr;

    auto it1 = mMap.find(aVolumeName);
    if (it1 != mMap.end())
    {
        auto it2 = it1->second.find(aNodeName);
        if (it2 != it1->second.end())
        {
            // TODO: warning? info?
            it2 = it1->second.find("*");
        }

        if (it2 != it1->second.end())
        {
            result = it2->second;
        }
        else
        {
            // TODO: error!
        }
    }
    else
    {
        // TODO: error!
    }

    return result;
}

//--------------------------------------------------------------------------------
