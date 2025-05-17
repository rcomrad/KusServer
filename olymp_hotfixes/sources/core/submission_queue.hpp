#ifndef SUBMISSION_QUEUE_HPP
#define SUBMISSION_QUEUE_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <queue>

#include "database/database_structures.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class SubmissionQueue
{
public:
    static SubmissionQueue& getInstance();

    bool isEmpty() noexcept;
    void push(data::Table<data::Submission>&& aSubmition) noexcept;
    data::Table<data::Submission> get() noexcept;

    // void checkSubmissionQueue() noexcept;
    void reload() noexcept;

private:
    SubmissionQueue();

    bool mIsActive;

    std::queue<data::Table<data::Submission>> mQueue;
    mutable std::mutex mSubmissionMutex;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !SUBMISSION_QUEUE_HPP
