#include <sys/stat.h>  // mkfifo
#include <sys/types.h> // mkfifo

#include <algorithm>
#include <fcntl.h>
#include <ranges>
#include <string>
#include <thread>
#include <vector>

#include "utility/common/transform.hpp"
#include "utility/datastructs/num_prefix_tree.hpp"

#include "fixture.hpp"

namespace kustest
{

class PipeExample : public Fixture
{
};

int
pipe_open(const std::string& name, int mode)
{
    int result;
    if ((result = open(name.c_str(), mode)) < 0)
    {
        throw std::runtime_error("Unable to open pipe " + name + " for " +
                                 (mode == O_RDONLY ? "read." : "write."));
    }
    return result;
}

void
foo(const std::string& to, const std::string& from)
{
#ifdef LINUS_LINUX
    std::string read_name  = "/tmp/" + to;
    std::string write_name = "/tmp/" + from;

    if (mkfifo(read_name.c_str(), 0600))
    {
    }

    int read_fd  = pipe_open(read_name, O_RDONLY);
    int write_fd = pipe_open(write_name, O_WRONLY);

    bool flag = to == "server";
    std::string to_send;
    while (true)
    {
        if (flag)
        {
            // if (write(write_fd, to_send.c_str(), to_send.size() + 1) < 0)
            // {
            //    throw std::runtime_error("Unable to write data to " + to + "
            //    pipe."));
            // }
        }
        else
        {
            // num = read(fifo, temp + tot, sizeof(temp) - tot);
        }
        std::cout << to << std::endl;
    }
#endif
}

TEST_F(PipeExample, smoke)
{
    std::cout << "start pipes" << std::endl;

    std::thread t1(foo, "server", "client");
    std::thread t2(foo, "client", "server");

    // foo("server", "client");
    // foo("client", "server");

    while (true);
}

} // namespace kustest
