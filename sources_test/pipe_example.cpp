#include <sys/stat.h>
#include <sys/types.h>

#include <chrono>
#include <condition_variable>
#include <fcntl.h>
#include <future>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <unistd.h>

#include "gtest/gtest.h"

#include "fixture.hpp"

const std::string SERVER_NAME = "server";
const std::string CLIENT_NAME = "client";

constexpr uint BUFFER_SIZE = 1024;
constexpr uint8_t DELAY    = 10;

namespace kustest
{

class PipeExample : public Fixture
{
};

class PipeReader
{
public:
    explicit PipeReader(const std::string& a_name) : m_name(a_name), m_fd(-1)
    {
        std::string path = "/tmp/" + a_name;
        if (mkfifo(path.c_str(), 0666) < 0 && errno != EEXIST)
        {
            throw std::runtime_error("Failed to create FIFO: " + path);
        }
    }

    ~PipeReader()
    {
        if (m_fd >= 0)
        {
            close(m_fd);
        }
        unlink(("/tmp/" + m_name).c_str());
    }

    std::optional<std::string> read()
    {
        if (m_fd < 0)
        {
            m_fd = open(("/tmp/" + m_name).c_str(), O_RDONLY | O_NONBLOCK);
            if (m_fd < 0)
            {
                return std::nullopt;
            }
        }

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read = ::read(m_fd, buffer, sizeof(buffer));

        if (bytes_read <= 0)
        {
            if (errno != EAGAIN)
            {
                return std::nullopt;
            }
            return std::nullopt;
        }

        return std::string(buffer, bytes_read - 1);
    }

private:
    std::string m_name;
    int m_fd;
};

class PipeWriter
{
public:
    explicit PipeWriter(const std::string& a_name) : m_name(a_name), m_fd(-1)
    {
        std::string path = "/tmp/" + a_name;
        if (mkfifo(path.c_str(), 0666) < 0 && errno != EEXIST)
        {
            throw std::runtime_error("Failed to create FIFO: " + path);
        }
    }

    ~PipeWriter()
    {
        if (m_fd >= 0)
        {
            close(m_fd);
        }
        unlink(("/tmp/" + m_name).c_str());
    }

    bool write(const std::string& a_data)
    {
        if (m_fd < 0)
        {
            m_fd = open(("/tmp/" + m_name).c_str(), O_WRONLY | O_NONBLOCK);
            if (m_fd < 0)
            {
                return false;
            }
        }

        ssize_t bytes_written =
            ::write(m_fd, a_data.c_str(), a_data.size() + 1);
        return bytes_written > 0;
    }

private:
    std::string m_name;
    int m_fd;
};

TEST_F(PipeExample, ThreadCommunicationClientWaitsServer)
{
    std::mutex mtx;
    std::condition_variable cv;
    bool server_ready = false;

    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();

    std::thread server_thread(
        [&]()
        {
            PipeReader server_reader(SERVER_NAME);
            PipeWriter server_writer(CLIENT_NAME);

            server_ready = true;
            cv.notify_one();

            std::optional<std::string> received_message;
            while (!(received_message = server_reader.read()))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
            }

            server_writer.write("This is message from " + SERVER_NAME);
            promise.set_value(*received_message);
        });

    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&server_ready] { return server_ready; });
    }

    PipeReader client_reader(CLIENT_NAME);
    PipeWriter client_writer(SERVER_NAME);

    client_writer.write("This is message from " + CLIENT_NAME);

    std::optional<std::string> response;
    while (!(response = client_reader.read()))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
    }

    EXPECT_EQ(*response, "This is message from " + SERVER_NAME);

    std::string server_received = future.get();
    EXPECT_EQ(server_received, "This is message from " + CLIENT_NAME);

    server_thread.join();
}

TEST_F(PipeExample, ThreadCommunicationServerWaitsClient)
{
    std::mutex mtx;
    std::condition_variable cv;
    bool client_ready = false;

    PipeReader client_reader(CLIENT_NAME);
    PipeWriter client_writer(SERVER_NAME);

    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();

    std::thread server_thread(
        [&]()
        {
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [&client_ready] { return client_ready; });
            }

            PipeReader server_reader(SERVER_NAME);
            PipeWriter server_writer(CLIENT_NAME);

            server_writer.write("This is message from " + SERVER_NAME);

            std::optional<std::string> received_message;
            while (!(received_message = server_reader.read()))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
            }

            promise.set_value(*received_message);
        });

    client_ready = true;
    cv.notify_one();

    std::optional<std::string> response;
    while (!(response = client_reader.read()))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
    }

    EXPECT_EQ(*response, "This is message from " + SERVER_NAME);

    client_writer.write("This is message from " + CLIENT_NAME);

    std::string server_received = future.get();
    EXPECT_EQ(server_received, "This is message from " + CLIENT_NAME);

    server_thread.join();
}

TEST_F(PipeExample, ProcessCommunicationClientWaitsServer)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        FAIL() << "Fork failed";
    }
    else if (pid == 0)
    {
        PipeReader server_reader(SERVER_NAME);
        PipeWriter server_writer(CLIENT_NAME);

        PipeWriter sync_writer("sync");
        sync_writer.write("ready");

        std::optional<std::string> received_message;
        while (!(received_message = server_reader.read()))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
        }

        server_writer.write("This is message from " + SERVER_NAME);
        exit(received_message == "This is message from " + CLIENT_NAME ? 0 : 1);
    }
    else
    {
        PipeReader sync_reader("sync");
        std::optional<std::string> sync_msg;
        while (!sync_msg)
        {
            sync_msg = sync_reader.read();
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
        }

        PipeReader client_reader(CLIENT_NAME);
        PipeWriter client_writer(SERVER_NAME);

        client_writer.write("This is message from " + CLIENT_NAME);

        std::optional<std::string> response;
        while (!(response = client_reader.read()))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
        }

        EXPECT_EQ(*response, "This is message from " + SERVER_NAME);

        int status;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status));
        EXPECT_EQ(WEXITSTATUS(status), 0);

        unlink("/tmp/sync");
    }
}

// TODO: Find out why analogical test with processes when child (server) waits
// for parent (client) is blocking.

} // namespace kustest
