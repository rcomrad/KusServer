// #include "callback_register.hpp"

// #include "callback_storage.hpp"

// core::CallbackRegister::CallbackRegister(const RegisterNode& aNode) noexcept
// {
//     registrate(aNode);
// }

// core::CallbackRegister::CallbackRegister(
//     const std::vector<RegisterNode>& aNodeList) noexcept
// {
//     for (const auto& i : aNodeList)
//     {
//         registrate(i);
//     }
// }

// void
// core::CallbackRegister::registrate(const RegisterNode& aNode) noexcept
// {
//     CallbackStorage::add(aNode.mVolumeName, aNode.mNodeName, aNode.mFunc);
// }
