#ifndef SUBMISSION_QUEUE_HPP
#define SUBMISSION_QUEUE_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <queue>

#include "database/data_array.hpp"
#include "database/database_structures.hpp"

//-----------------d---------------------------------------------------------------

namespace core
{
class SubmissionQueue
{
public:
    static SubmissionQueue& getInstance();

    bool isEmpty() noexcept;
    void push(data::Submission&& aSubmition) noexcept;
    data::Submission get() noexcept;

    // void checkSubmissionQueue() noexcept;
    void reload() noexcept;

private:
    SubmissionQueue();

    bool mIsActive;

    data::DataArray<data::Submission> mQueue;
    mutable std::mutex mSubmissionMutex;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !SUBMISSION_QUEUE_HPP
