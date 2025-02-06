#pragma once

#include <stdexcept>

#include "kernel/framework/module/kernel.hpp"
#include "kernel/utility/synchronization/condvar.hpp"

#include "definitions.hpp"

namespace kustest
{

template <typename ModuleType>
class SinglUseModule : public ModuleType
{
public:
    SinglUseModule() : ModuleType("test_module")
    {
    }

protected:
    bool loopBody() override
    {
        return m_loop_cnt++ < 1;
    }

private:
    int m_loop_cnt = 0;
};

template <typename ModuleType>
class InfinityModule : public SinglUseModule<ModuleType>
{
protected:
    bool loopBody() override
    {
        return true;
    }
};

template <typename ModuleType>
class SelfExitModule : public SinglUseModule<ModuleType>
{
protected:
    void terminate() override
    {
        KERNEL.stop();
    }
};

template <typename ModuleType>
class NoLoopMode : public SinglUseModule<ModuleType>
{
protected:
    bool loopBody() final
    {
        return false;
    }
    void terminate() final
    {
        KERNEL.stop();
    }
};

template <typename ModuleType>
class InitThrowModule : public SinglUseModule<ModuleType>
{
private:
    void initialize() final
    {
        throw std::runtime_error("Test exception");
    }
};

template <typename ModuleType, int TermCount>
class LoopThrowModule : public SinglUseModule<ModuleType>
{
    using Base = SinglUseModule<ModuleType>;

protected:
    bool loopBody() override
    {
        m_cur_iteration++;

        if (m_cur_iteration == TermCount)
        {
            throw std::runtime_error("Test exception");
        }
        else if (m_cur_iteration > TermCount)
        {
            return false;
        }

        return true;
    }

private:
    int m_cur_iteration = -1;
};

template <typename ModuleType>
class FirstLoopThrowModule : public LoopThrowModule<ModuleType, 0>
{
};

template <typename ModuleType>
class SecondLoopThrowModule : public LoopThrowModule<ModuleType, 1>
{
};

template <typename ModuleType>
class TerminateThrowModule : public SinglUseModule<ModuleType>
{
private:
    void terminate() final
    {
        throw std::runtime_error("Test exception");
    }
};

} // namespace kustest
