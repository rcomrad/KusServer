// #ifndef ROUTER_STORAGE_HPP
// #define ROUTER_STORAGE_HPP

// //--------------------------------------------------------------------------------

// #include <string>
// #include <unordered_map>
// #include <unordered_set>

// #include "router.hpp"

// //--------------------------------------------------------------------------------

// namespace dom
// {

// class RegistrateRote
// {
// public:
//     static void addRouter(const std::string& aName, void* aRouter) noexcept;

//     template <typename TFunc>
//     static void addRouterPath(const std::string& aRouterName,
//                               const std::unordered_set<std::string>& aPathNames,
//                               TFunc* aFunck) noexcept
//     {
//         getInstance().addRouterPathNonstatic<TFunc>(aRouterName, aPathNames,
//                                                     aFunck);
//     }

// private:
//     static RegistrateRote& getInstance() noexcept;

//     void addRouterNonstatic(const std::string& aName, void* aRouter) noexcept;

//     template <typename TFunc>
//     void addRouterPathNonstatic(
//         const std::string& aRouterName,
//         const std::unordered_set<std::string>& aPathNames,
//         TFunc* aFunck) noexcept
//     {
//         auto it = mRouterStorage.find(aRouterName);
//         if (it != mRouterStorage.end())
//         {
//             static_cast<Router<TFunc>*>(it->second)
//                 ->addPath(aPathNames, aFunck);
//         }
//         else
//         {
//             dom::WRITE_LOG_ERROR
//         }
//     }

//     std::unordered_map<std::string, void*> mRouterStorage;
// };

// } // namespace dom

// //--------------------------------------------------------------------------------

// #endif // !ROUTER_STORAGE_HPP
