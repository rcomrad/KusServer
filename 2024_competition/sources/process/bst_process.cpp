#ifdef BOOST_PROCESS

#    include "bst_process.hpp"

//--------------------------------------------------------------------------------

#    include "domain/log.hpp"

//--------------------------------------------------------------------------------

proc::BoostProcess::BoostProcess() noexcept
{
}

proc::BoostProcess::BoostProcess(const BoostProcess& other) noexcept
{
    *this = other;
}

proc::BoostProcess&
proc::BoostProcess::operator=(const BoostProcess& other) noexcept
{
    mProcessArgs = other.mProcessArgs;
    return *this;
}

//--------------------------------------------------------------------------------

void
proc::BoostProcess::setComand(
    const std::vector<std::string>& aParameters) noexcept
{
    for (auto& i : aParameters) mProcessArgs += i + " ";
    if (mProcessArgs.size()) mProcessArgs.pop_back();
}

//--------------------------------------------------------------------------------

void
proc::BoostProcess::create() noexcept
{
    IORedirection();

    // WRITE_LOG("Creating_process_with_name:", mProcessArgs);
    // bp::child temp(mProcessArgs, bp::std_out > out, bp::std_in < in,
    //                bp::start_suspended);
    // mProcess = std::move(temp);

    // dom::writeInfo("Creating_process_with_name:", mProcessArgs);
    // dom::writeInfo("Runing_simple_process");

    try
    {
        bp::child temp(mProcessArgs, bp::std_out > in, bp::std_in < out);
        mProcess = std::move(temp);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

//--------------------------------------------------------------------------------

bool
proc::BoostProcess::run() noexcept
{
    // mProcess.resume();
    try
    {
        mProcess.wait_for(std::chrono::milliseconds(5000));
        flag = !mProcess.running();
    }
    catch (const std::exception& e)
    {
        flag = false;
        std::cerr << e.what() << '\n';
    }
    return flag;
}

//--------------------------------------------------------------------------------

std::optional<Limits>
proc::BoostProcess::runWithLimits() noexcept
{
    // dom::writeInfo("Runing_process_with_time_and_memory_evaluation");

    std::optional<Limits> result = {};

    uint64_t timeUsage   = 100;
    uint64_t memoryUsage = 1;

    try
    {
        mProcess.wait_for(std::chrono::milliseconds(mTimeLimit));
        result = {timeUsage, memoryUsage};
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        flag = false;
    }

    return result;
}

//--------------------------------------------------------------------------------

void
proc::BoostProcess::IORedirection() noexcept
{
    out = std::move(bp::opstream());
    in  = std::move(bp::ipstream());
}

//--------------------------------------------------------------------------------

void
proc::BoostProcess::readData(std::string& result) noexcept
{
    std::string line;
    while (flag && std::getline(in, line) && !line.empty())
    {
        // if (!mProcess.running() && line.empty()) break;
        result += std::move(line);
    }
}

//--------------------------------------------------------------------------------

void
proc::BoostProcess::writeData(const std::string& aMessage) noexcept
{
    out << aMessage;
}

//--------------------------------------------------------------------------------

#endif // !BOOST_PROCESS
