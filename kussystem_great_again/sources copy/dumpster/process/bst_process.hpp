#ifndef MY_BOOST_PROCESS_HPP
#define MY_BOOST_PROCESS_HPP

#ifdef BOOST_PROCESS

//--------------------------------------------------------------------------------

#    include <string>

#    include "boost/process.hpp"

namespace bp = boost::process;

#    include "base_process.hpp"

namespace proc
{
class BoostProcess : public BaseProcess
{
public:
    BoostProcess() noexcept;
    virtual ~BoostProcess() = default;

    BoostProcess(const BoostProcess& other) noexcept;
    BoostProcess& operator=(const BoostProcess& other) noexcept;

    BoostProcess(BoostProcess&& other) noexcept            = default;
    BoostProcess& operator=(BoostProcess&& other) noexcept = default;

    void setComand(
        const std::vector<str::String>& aParameters) noexcept final override;

    void create() noexcept final override;

    bool run() noexcept final override;
    std::optional<Limits> runWithLimits() noexcept final override;

    virtual void IORedirection() noexcept;
    void readData(char* result) noexcept final override;
    void writeData(const char* aMessage) noexcept final override;

private:
    bp::child mProcess;
    bp::opstream out;
    bp::ipstream in;
    bool flag = true;

    str::String mProcessArgs;
};
} // namespace proc

//--------------------------------------------------------------------------------

#endif // !BOOST_PROCESS

#endif // !MY_BOOST_PROCESS_HPP