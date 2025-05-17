// #pragma once

// //--------------------------------------------------------------------------------

// #include <string>

// #include "kernel/utility/synchronization/condvar.hpp"
// #include "kernel/utility/type/declaration/lifecycle_manager.hpp"

// //--------------------------------------------------------------------------------

// namespace core
// {
// class ModuleBase
// {
// public:
//     ModuleBase(const char* a_name, bool create_status_subscription = false);
//     virtual ~ModuleBase() = default;

//     const std::string& getName() const noexcept;
//     const std::string& getStatusName() const noexcept;
//     const util::Condvar& subscribeToStatusUpdate() const;

//     void close() noexcept;

// protected:
//     enum class Status
//     {
//         CREATED,
//         INITIALIZED,
//         ALIVE,
//         CLOSING,
//         TERMINATED,
//         KILLED
//     };
//     Status getStatus() const noexcept;

//     virtual void initialize() = 0;
//     virtual bool loopBody()   = 0;
//     virtual void terminate()  = 0;

//     void kill() noexcept;

//     void setVariable(int a_variable_num, int a_variable_value) const
//     noexcept; int getVariable(int a_variable_num) const noexcept;

// private:
//     std::string m_name;
//     size_t m_variable_offset;
//     Status m_status;
//     util::LifecycleManager<util::Condvar> m_status_update;
// };

// } // namespace core

// //------------------------------------------------------------------------------
