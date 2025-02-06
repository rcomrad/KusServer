#include "kernel/tester/kernel_fixture.hpp"

//------------------------------------------------------------------------------

#include "definitions.hpp"
#include "module_sync.hpp"
#include "testerapi_sync.hpp"

//------------------------------------------------------------------------------

namespace kustest
{

class USyncModuleTest : public KernelFixture
{
};

TEST_F(USyncModuleTest, singl_use_test)
{
    SyncModuleTester<SinglUseModule> tester;
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING,
                            MState::TERMINATED});
    tester.exec();
}

TEST_F(USyncModuleTest, init_throw)
{
    SyncModuleTester<InitThrowModule> tester;
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::KILLED});
    tester.exec();
}

TEST_F(USyncModuleTest, no_loop_test)
{
    SyncModuleTester<NoLoopMode> tester;
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::CLOSING, MState::TERMINATED});
    tester.exec();
}

TEST_F(USyncModuleTest, loop_first_throw)
{
    SyncModuleTester<FirstLoopThrowModule> tester;
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE_WITH_EXCEPTIONS, MState::CLOSING,
                            MState::TERMINATED});
    tester.exec();
}

TEST_F(USyncModuleTest, loop_second_throw)
{
    SyncModuleTester<SecondLoopThrowModule> tester;
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::ALIVE_WITH_EXCEPTIONS,
                            MState::CLOSING, MState::TERMINATED});
    tester.exec();
}

TEST_F(USyncModuleTest, term_throw)
{
    SyncModuleTester<TerminateThrowModule> tester;
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING, MState::KILLED});
    tester.exec();
}

TEST_F(USyncModuleTest, external_module_kill)
{
    SyncExternalKillTester<InfinityModule> tester;
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING,
                            MState::TERMINATED});
    tester.exec();
}

} // namespace kustest
