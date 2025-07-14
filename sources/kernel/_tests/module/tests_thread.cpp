#include "kernel/tester/commands_fixture.hpp"

//------------------------------------------------------------------------------

#include "definitions.hpp"
#include "module_sync.hpp"
#include "testerapi_thread.hpp"

//------------------------------------------------------------------------------

// TODO:
/*
clang-format off 

D:\projects\KusServer\sources\kernel\_tests\module\tester_sync.hpp(61): error: Expected equality of these values:
  a_result
    Which is: { 4-byte object <00-00 00-00>, 4-byte object <03-00 00-00>, 4-byte object <0C-00 00-00> }
  a_answer
    Which is: { 4-byte object <00-00 00-00>, 4-byte object <0C-00 00-00> }
thread

clang-format on
*/

namespace kustest
{

class UThreadModuleTest : public CommandsFixture
{
};

TEST_F(UThreadModuleTest, singl_use_test)
{
    ThreadSelfCloser<SinglUseModule> tester(*this);
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
    ThreadModuleTester<InitThrowModule> tester(*this);
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::KILLED});
    tester.setThreadStates({MState::NUN, MState::IDLE});
    tester.exec();
}

TEST_F(UThreadModuleTest, no_loop_test)
{
    ThreadSelfCloser<NoLoopMode> tester(*this);
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::CLOSING, MState::TERMINATED});
    tester.setThreadStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING,
                            MState::TERMINATED});
    tester.exec();
}

TEST_F(UThreadModuleTest, term_throw)
{
    ThreadSelfCloser<TerminateThrowModule> tester(*this);
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING, MState::KILLED});
    tester.setThreadStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING,
                            MState::TERMINATED});
    tester.exec();
}

TEST_F(UThreadModuleTest, external_module_kill)
{
    ThreadExternalKillTester<InfinityModule> tester(*this);
    tester.setModuleStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING,
                            MState::TERMINATED});
    tester.setThreadStates({MState::NUN, MState::CREATED, MState::INITIALIZED,
                            MState::ALIVE, MState::CLOSING,
                            MState::TERMINATED});
    tester.exec();
}

} // namespace kustest
