#include "submission_queue.hpp"

#include "database/connection_manager.hpp"

#include "program_state.hpp"

core::SubmissionQueue::SubmissionQueue()
{
    mIsActive = ProgramState::getInstance().checkFlag(Flag::SUB_CHECK);
}

core::SubmissionQueue&
core::SubmissionQueue::getInstance()
{
    static SubmissionQueue instance;
    return instance;
}

bool
core::SubmissionQueue::isEmpty() noexcept
{
    return mQueue.empty();
}

void
core::SubmissionQueue::push(
    data::Table<data::Submission>&& aSubmission) noexcept
{
    if (mIsActive)
    {
        mSubmissionMutex.lock();
        mQueue.push(std::move(aSubmission));
        mSubmissionMutex.unlock();
    }
}

data::Table<data::Submission>
core::SubmissionQueue::get() noexcept
{
    data::Table<data::Submission> temp = std::move(mQueue.front());
    mQueue.pop();
    return std::move(temp);
}

// void
// core::SubmissionQueue::checkSubmissionQueue() noexcept
// {
//     if (mIsActive)
//     {
//         mSubmissionMutex.lock();
//         decltype(mQueue) empty;
//         std::swap(mQueue, empty);
//         if (mRestartState != Restart::EMPTY) reloadSubmissionQueue();
//         mSubmissionMutex.unlock();
//     }
// }

void
core::SubmissionQueue::reload() noexcept
{

    mSubmissionMutex.lock();
    decltype(mQueue) empty;
    std::swap(mQueue, empty);
    auto connection = data::ConnectionManager::getUserConnection();
    auto problemTable =
        connection.val.getData<data::Submission>("verdict=\'NUN\'");

    for (auto& i : problemTable)
    {
        data::Table<data::Submission> sub;
        sub.emplace_back(std::move(i));
    }
    mSubmissionMutex.unlock();
}
