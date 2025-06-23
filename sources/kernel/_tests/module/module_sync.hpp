#pragma once

#include <atomic>
#include <stdexcept>

#include "kernel/framework/core/kernel.hpp"
#include "kernel/utility/synchronization/condvar.hpp"
#include "kernel/utility/synchronization/sleep.hpp"

#include "definitions.hpp"

namespace kustest
{

template <typename ModuleType>
class SinglUseModule : public ModuleType
{
public:
    SinglUseModule(util::Condvar& a_has_started)
        : ModuleType("test_module"), m_has_started(a_has_started)
    {
    }

protected:
    void initialize() override
    {
        m_has_started.notify();
    }

    bool loopBody() override
    {
        return m_loop_cnt++ < 1;
    }

private:
    int m_loop_cnt = 0;
    util::Condvar& m_has_started;
};

template <typename ModuleType>
class InfinityModule : public SinglUseModule<ModuleType>
{
    using Base = SinglUseModule<ModuleType>;
    using Base::Base;

protected:
    bool loopBody() override
    {
        return true;
    }
};

template <typename ModuleType>
class NoLoopMode : public SinglUseModule<ModuleType>
{
    using Base = SinglUseModule<ModuleType>;
    using Base::Base;

protected:
    bool loopBody() final
    {
        return false;
    }
};

template <typename ModuleType>
class InitThrowModule : public SinglUseModule<ModuleType>
{
    using Base = SinglUseModule<ModuleType>;
    using Base::Base;

private:
    void initialize() final
    {
        Base::initialize();
        throw std::runtime_error("Test exception");
    }
};

template <typename ModuleType, int TermCount>
class LoopThrowModule : public SinglUseModule<ModuleType>
{
    using Base = SinglUseModule<ModuleType>;
    using Base::Base;

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
    using Base = LoopThrowModule<ModuleType, 0>;
    using Base::Base;
};

template <typename ModuleType>
class SecondLoopThrowModule : public LoopThrowModule<ModuleType, 1>
{
    using Base = LoopThrowModule<ModuleType, 1>;
    using Base::Base;
};

template <typename ModuleType>
class TerminateThrowModule : public SinglUseModule<ModuleType>
{
    using Base = SinglUseModule<ModuleType>;
    using Base::Base;

private:
    void terminate() final
    {
        throw std::runtime_error("Test exception");
    }
};

} // namespace kustest
