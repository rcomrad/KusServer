// #ifndef ROUTER_HPP
// #define ROUTER_HPP

// //--------------------------------------------------------------------------------

// #include <string>
// #include <unordered_map>

// //--------------------------------------------------------------------------------

// namespace dom
// {

// template <typename TFunc>
// struct Router
// {
// public:
//     void addPath(const std::unordered_set<std::string>& aNames,
//                  TFunc* aFunck) noexcept
//     {
//         mAddingMutex.lock();
//         for (auto& i : aNames)
//         {
//             mRouter[i] = aFunck;
//         }
//         mAddingMutex.unlock();
//     }

//     TFunc* getFuncPtr(const std::string& aName) const noexcept
//     {
//         TFunc* result = nullptr;
//         auto it       = mRouter.find(aName);
//         if (it != mRouter.end())
//         {
//             result = it->second;
//         }
//         else
//         {
//             dom::WRITE_LOG_ERROR
//         }
//         return result;
//     }

// private:
//     std::mutex mAddingMutex;
//     std::unordered_map<std::string, TFunc*> mRouter;
// };

// } // namespace dom

// //--------------------------------------------------------------------------------

// #endif // !ROUTER_HPP
