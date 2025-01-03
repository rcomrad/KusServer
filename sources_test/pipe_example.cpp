#include <sys/stat.h>
#include <sys/types.h>

#include <chrono>
#include <fcntl.h>
#include <future>
#include <string>
#include <thread>
#include <unistd.h>

#include "gtest/gtest.h"

#include "fixture.hpp"

std::string SERVER_NAME = "server";
std::string CLIENT_NAME = "client";

uint8_t MAX_PIPE_AWAITING_ITERS = 10;
uint8_t SLEEP_INTERVAL          = 100;
uint BUFFER_SIZE                = 1024;

namespace kustest
{

class PipeExample : public Fixture
{
public:
    void setUp() noexcept override
    {
        cleanup_pipes();
    }
    void tearDown() noexcept override
    {
        cleanup_pipes();
    }

private:
    void cleanup_pipes()
    {
        unlink("/tmp/client");
        unlink("/tmp/server");
    }
};

std::string
pipe_communicate(const std::string& read_name,
                 const std::string& write_name,
                 const std::string& message)
{
    std::string read_path  = "/tmp/" + read_name;
    std::string write_path = "/tmp/" + write_name;

    if (mkfifo(read_path.c_str(), 0666) < 0 && errno != EEXIST)
    {
        std::cerr << "Failed to create input FIFO: " << read_path << std::endl;
        return "corrupted fs";
    }

    if (mkfifo(write_path.c_str(), 0666) < 0 && errno != EEXIST)
    {
        std::cerr << "Failed to create output FIFO: " << read_path << std::endl;
        return "corrupted fs";
    }

    int iter = 0;
    while (true)
    {
        iter++;

        int read_fd = open(read_path.c_str(), O_RDONLY | O_NONBLOCK);
        if (read_fd < 0)
        {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(SLEEP_INTERVAL));
            continue;
        }

        int write_fd = open(write_path.c_str(), O_WRONLY | O_NONBLOCK);
        if (write_fd < 0)
        {
            if (iter > MAX_PIPE_AWAITING_ITERS)
            {
                return "non existing pipe";
            }

            close(read_fd);
            std::this_thread::sleep_for(
                std::chrono::milliseconds(SLEEP_INTERVAL));
            continue;
        }

        write(write_fd, message.c_str(), message.size() + 1);

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read = 0;
        while (bytes_read <= 0)
        {
            bytes_read = read(read_fd, buffer, sizeof(buffer));
            if (bytes_read < 0)
            {
                if (errno != EAGAIN)
                {
                    close(read_fd);
                    close(write_fd);
                    return "read error";
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }

        close(write_fd);
        close(read_fd);
        return buffer;
    }
    return "broken pipe";
}

TEST_F(PipeExample, ThreadCommunication)
{
    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();

    std::thread child_thread(
        [&promise]()
        {
            std::string result =
                pipe_communicate(SERVER_NAME, CLIENT_NAME,
                                 "This is message from " + SERVER_NAME);
            promise.set_value(result);
        });

    EXPECT_EQ(pipe_communicate(CLIENT_NAME, SERVER_NAME,
                               "This is message from " + CLIENT_NAME),
              "This is message from server");

    std::string child_result = future.get();
    EXPECT_EQ(child_result, "This is message from client");

    child_thread.join();
}

TEST_F(PipeExample, MissingPipe)
{
    EXPECT_EQ(pipe_communicate(SERVER_NAME, "nonexisting", "Any message"),
              "non existing pipe");
    unlink("/tmp/nonexisting");
}

TEST_F(PipeExample, ClosedPipe)
{
    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();

    std::thread child_thread(
        [&promise]()
        {
            std::string result =
                pipe_communicate(SERVER_NAME, CLIENT_NAME,
                                 "This is message from " + SERVER_NAME);
            promise.set_value(result);
            unlink("/tmp/client");
            unlink("/tmp/server");
        });

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_INTERVAL * 5));
    EXPECT_EQ(pipe_communicate(CLIENT_NAME, SERVER_NAME,
                               "This is message from " + CLIENT_NAME),
              "This is message from server");

    std::string child_result = future.get();
    EXPECT_EQ(child_result, "This is message from client");

    child_thread.join();
}

/*TEST_F(PipeExample, ProcessCommunication)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        FAIL() << "Fork failed";
    }
    else if (pid == 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_INTERVAL));

        pipe_communicate(SERVER_NAME, CLIENT_NAME,
                         "This is message from " + SERVER_NAME);

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_INTERVAL));

        auto result = pipe_communicate(SERVER_NAME, CLIENT_NAME,
                                       "This is message from " + SERVER_NAME);
        if (result != "This is message from client")
        {
            std::cout << result << std::endl;
            exit(1);
        }
        exit(0);
    }
    else
    {
        EXPECT_EQ(pipe_communicate(CLIENT_NAME, SERVER_NAME,
                                   "This is message from " + CLIENT_NAME),
                  "This is message from server");

        int status;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status));
        EXPECT_EQ(WEXITSTATUS(status), 0);
    }
}*/

} // namespace kustest
