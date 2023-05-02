#include "data_request.hpp"

#include "database_structures.hpp"

std::unordered_map<std::string, std::string> data::DataRequest::aTableNames = {
    {"methodist", "user"},
    {"teacher",   "user"}
};

data::DataRequest::DataRequest(const std::string& aRequest,
                               std::string&& aCondition) noexcept
{
    mCondition = std::move(aCondition);

    int curPrev = -1;
    int last    = 0;
    for (int iter = 0; iter < aRequest.size() + 1; ++iter)
    {
        switch (aRequest[iter])
        {
            case '[':
                curPrev = mTables.size();
                pushTable(iter, last, aRequest, curPrev ? 3 : 0);
                break;

            case '\0':
                if (mTables.empty())
                {
                    pushTable(iter, last, aRequest, 0);
                    break;
                }
            case ']':
            case ';':
                pushName(iter, last, aRequest, curPrev);
                if (aRequest[iter] == ']') curPrev = mPrev[curPrev];
                break;
                // case '-':
                // case '+':
                // case '\\':
                //     // TODO: ban
                //     break;
        }
    }

    for (auto& i : mNicknames)
    {
        auto it = aTableNames.find(i);
        if (it != aTableNames.end())
        {
            mTables.emplace_back(it->second);
        }
        else
        {
            mTables.emplace_back(i);
        }
    }
}

std::string
data::DataRequest::getTables() const noexcept
{
    std::string result = "journal." + mTables[0] + " ";
    for (size_t i = 1; i < mTables.size(); ++i)
    {
        result += "inner join journal." + mTables[i] + " on journal." +
                  mTables[mPrev[i]] + "." + mTables[i] + "_id" + " = journal." +
                  mTables[mPrev[i]] + ".id ";
    }
    return result;
}

std::string
data::DataRequest::getColumns() const noexcept
{
    std::string result;

    for (size_t i = 0; i < mColumns.size(); ++i)
    {
        for (auto& j : mColumns[i])
        {
            result += "journal." + mTables[i] + "." + j + ", ";
        }
    }

    if (!result.empty()) result.resize(result.size() - 2);

    return result;
}

const std::string&
data::DataRequest::getCondition() const noexcept
{
    return mCondition;
}

const std::string&
data::DataRequest::getTableName(size_t aNum) const noexcept
{
    return mTables[aNum];
}

std::string
data::DataRequest::getNickname(size_t aNum) const noexcept
{
    return mNicknames[aNum];
}

const std::unordered_set<std::string>&
data::DataRequest::getTableColumns(size_t aNum) const noexcept
{
    return mColumns[aNum];
}

int
data::DataRequest::getPreviousNum(size_t aNum) const noexcept
{
    return mPrev[aNum];
}

size_t
data::DataRequest::size() const noexcept
{
    return mTables.size();
}

void
data::DataRequest::pushTable(int iter,
                             int& last,
                             const std::string& aRequest,
                             int aOffset) noexcept
{
    if (iter - last > 1)
    {
        mColumns.emplace_back();
        mNicknames.emplace_back(aRequest.substr(last, iter - last - aOffset));
    }
    last = iter + 1;
}

void
data::DataRequest::pushName(int iter,
                            int& last,
                            const std::string& aRequest,
                            int curPrev) noexcept
{
    if (iter - last > 1)
    {
        mColumns[curPrev].insert(aRequest.substr(last, iter - last));
    }
    last = iter + 1;
}
