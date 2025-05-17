#include "submission_queue.hpp"

#include "database/connection_manager.hpp"

#include "domain/variable_storage.hpp"

core::SubmissionQueue::SubmissionQueue()
{
    mIsActive = dom::VariableStorage::touchFlag("submission_auto_check");
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
    const std::lock_guard<std::mutex> lock(mSubmissionMutex);
    return mQueue.empty();
}

void
core::SubmissionQueue::push(data::Submission&& aSubmission) noexcept
{
    if (mIsActive)
    {
        mSubmissionMutex.lock();
        mQueue.emplace_back(std::move(aSubmission));
        mSubmissionMutex.unlock();
    }
}

data::Submission
core::SubmissionQueue::get() noexcept
{
    const std::lock_guard<std::mutex> lock(mSubmissionMutex);
    data::Submission temp = std::move(mQueue.back());
    mQueue.pop_back();
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
    auto mQueue =
        connection.val.getDataArray<data::Submission>("verdict=\'NUN\'");
    mSubmissionMutex.unlock();
}
