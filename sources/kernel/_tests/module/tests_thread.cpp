#include "kernel/tester/kernel_fixture.hpp"

//------------------------------------------------------------------------------

#include "definitions.hpp"
#include "module_sync.hpp"
#include "testerapi_thread.hpp"

//------------------------------------------------------------------------------

namespace kustest
{

class UThreadModuleTest : public KernelFixture
{
};

TEST_F(UThreadModuleTest, singl_use_test)
{
    ThreadSelfCloser<SinglUseModule> tester;
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING,
                            MState::TERMINATED});

    tester.setThreadStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING,
                            MState::TERMINATED});
    tester.exec();
}

TEST_F(UThreadModuleTest, init_throw)
{
    ThreadModuleTester<InitThrowModule> tester;
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::KILLED});
    tester.setThreadStates({MState::NUN, MState::IDLE});
    tester.exec();
}

TEST_F(UThreadModuleTest, no_loop_test)
{
    ThreadSelfCloser<NoLoopMode> tester;
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::CLOSING, MState::TERMINATED});
    tester.setThreadStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING,
                            MState::TERMINATED});
    tester.exec();
}

TEST_F(UThreadModuleTest, term_throw)
{
    ThreadSelfCloser<TerminateThrowModule> tester;
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING, MState::KILLED});
    tester.setThreadStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING,
                            MState::TERMINATED});
    tester.exec();
}

TEST_F(UThreadModuleTest, external_module_kill)
{
    ThreadExternalKillTester<InfinityModule> tester;
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING,
                            MState::TERMINATED});
    tester.setThreadStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING,
                            MState::TERMINATED});
    tester.exec();
}

} // namespace kustest
