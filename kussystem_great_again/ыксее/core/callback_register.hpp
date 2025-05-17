// #pragma once

// //--------------------------------------------------------------------------------

// #include <vector>

// #include "string/kus_string.hpp"

// #include "holy_trinity.hpp"

// //--------------------------------------------------------------------------------

// namespace core
// {
// class CallbackRegister
// {
// public:
//     HOLY_TRINITY_SINGLE(CallbackRegister);

//     struct RegisterNode
//     {
//         const char* mVolumeName;
//         const char* mNodeName;
//         void* mFunc;
//     };

//     CallbackRegister(const RegisterNode& aNode) noexcept;
//     CallbackRegister(const std::vector<RegisterNode>& aNodeList) noexcept;

// private:
//     void registrate(const RegisterNode& aNode) noexcept;
// };
// } // namespace core

// //--------------------------------------------------------------------------------
