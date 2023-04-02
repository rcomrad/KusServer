#ifndef PIPE_LINUX_PROCESS_HPP
#define PIPE_LINUX_PROCESS_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "boost/process.hpp"

namespace bp = boost::process;

#include "base_process.hpp"

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
        const std::vector<std::string>& aParameters) noexcept final override;

    void create() noexcept final override;

    bool run() noexcept final override;
    std::optional<dom::Pair<uint64_t>> runWithLimits() noexcept final override;

    virtual void IORedirection() noexcept;
    void readData(std::string& result) noexcept final override;
    void writeData(const std::string& aMessage) noexcept final override;

private:
    bp::child mProcess;
    bp::opstream out;
    bp::ipstream in;
    bool flag = true;

    std::string mProcessArgs;
};
} // namespace proc

//--------------------------------------------------------------------------------

#endif // !PIPE_LINUX_PROCESS_HPP