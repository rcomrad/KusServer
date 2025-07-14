#pragma once

//--------------------------------------------------------------------------------

#include "module.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class ThreadModule;

class ThreadModuleInterface : public Module
{
public:
    ThreadModuleInterface(const std::string& a_name,
                          ThreadModule& a_thread_mpdule_ref);
    virtual ~ThreadModuleInterface() = default;

protected:
    void initialize() final;
    bool loopBody() final;
    void terminate() final;

private:
    ThreadModule& m_thread_module_ref;
};

} // namespace core

//------------------------------------------------------------------------------
