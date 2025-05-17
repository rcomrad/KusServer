// #include "module_base.hpp"

// #include "kernel/framework/logger/include_me.hpp"
// #include "kernel/framework/module/kernel.hpp"
// #include "kernel/utility/common/exception.hpp"

// // #include "registry.hpp"
// #include "base.hpp"

// core::ModuleBase::ModuleBase(const char* a_name,
//                              bool create_status_subscription)
//     : m_name(a_name),
//       m_variable_offset(KERNEL.getCurrentOffset()),
//       m_status(Status::CREATED)
// {
//     if (create_status_subscription)
//     {
//         m_status_update.create();
//     }
// }

// //------------------------------------------------------------------------------
// // ModuleBase body
// //------------------------------------------------------------------------------

// void
// core::ModuleBase::initialize()
// {
//     LOG_INFO("Dummy '%s' ModuleBase initialization.", m_name);
// }

// bool
// core::ModuleBase::loopBody()
// {
//     LOG_INFO("Dummy '%s' ModuleBase loop body.", m_name);
//     return false;
// }

// void
// core::ModuleBase::terminate()
// {
//     LOG_INFO("Dummy '%s' ModuleBase termination.", m_name);
// }

// //------------------------------------------------------------------------------
// // ModuleBase real life-cycle methods
// //------------------------------------------------------------------------------

// const std::string&
// core::ModuleBase::getName() const noexcept
// {
//     return m_name;
// }

// const std::string&
// core::ModuleBase::getStatusName() const noexcept
// {
//     static std::vector<std::string> g_status_types = {
//         "created", "initiakize", "alive", "closing", "terminated", "killed"};
//     using StatusType = std::underlying_type_t<Status>;
//     return g_status_types[static_cast<StatusType>(m_status)];
// }

// core::ModuleBase::Status
// core::ModuleBase::getStatus() const noexcept
// {
//     return m_status;
// }

// const util::Condvar&
// core::ModuleBase::subscribeToStatusUpdate() const
// {
//     if (!m_status_update)
//     {
//         THROW("Can't subscribe to status change: status subscription wasn't "
//               "set up and class creation stage.");
//     }
//     return m_status_update.obj;
// }

// void
// core::ModuleBase::close() noexcept
// {
//     m_status = Status::CLOSING;
//     if (m_status_update)
//     {
//         m_status_update.obj.notifyAll();
//     }
// }

// void
// core::ModuleBase::kill() noexcept
// {
//     m_status = Status::KILLED;
//     if (m_status_update)
//     {
//         m_status_update.obj.notifyAll();
//     }
// }

// //------------------------------------------------------------------------------
// // ModuleBase variable handlers
// //------------------------------------------------------------------------------

// void
// core::ModuleBase::setVariable(int a_variable_num,
//                               int a_variable_value) const noexcept
// {
//     KERNEL.setVariable(m_variable_offset + a_variable_num, a_variable_value);
// }

// int
// core::ModuleBase::getVariable(int a_variable_num) const noexcept
// {
//     return KERNEL.getVariable(m_variable_offset + a_variable_num);
// }

// //------------------------------------------------------------------------------
