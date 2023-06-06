#include "data_request.hpp"

#include "database_structures.hpp"

#include "file/file.hpp"

std::unordered_map<std::string, std::string> data::DataRequest::mActualNames = {
    {"methodist", "user"},
    {"teacher",   "user"}
};

data::DataRequest
data::RequestParser::process(const std::string& aRequest,
                             const std::string& aCondition) noexcept
{
    parse(aRequest);
    arrangeActualNames();
    arrangeColumns();

    DataRequest result;
    result.statement = "SELECT " + getColumns() + " FROM " + getTables() +
                       (aCondition.empty() ? "" : " WHERE " + aCondition);

    result.size = mPrev.size();
    for (size_t i = 0; i < result.size; ++i)
    {
        auto& temp    = result.tables.emplace_back();
        temp.prev     = mPrev[i];
        temp.name     = mTables[i];
        temp.nickname = mNicknames[i];
        temp.columns  = mColumns[i];
    }

    return result;
}

std::string
data::DataRequest::getTables() const noexcept
{
    std::string result = "journal." + mTables[0] + " ";
    for (size_t i = 1; i < mTables.size(); ++i)
    {
        result += "inner join journal." + mTables[i] + " on journal." +
                  mTables[mPrev[i]] + "." + mTables[i] + "_id" + " = journal." +
                  mTables[i] + ".id ";
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

void
data::DataRequest::parse(const std::string& aRequest) noexcept
{
    int curPrev = 0;
    int last    = 0;
    for (int iter = 0; iter < aRequest.size() + 1; ++iter)
    {
        switch (aRequest[iter])
        {
            case '[':
                mPrev.emplace_back(curPrev);
                curPrev = mNicknames.size();
                pushTable(iter, last, aRequest, curPrev ? 3 : 0);
                break;

            case '\0':
                if (mNicknames.empty())
                {
                    pushTable(iter, last, aRequest, 0);
                    break;
                }
            case ']':
            case ';':
                pushName(iter, last, aRequest, curPrev);
                if (aRequest[iter] == ']') curPrev = mPrev[curPrev];
                break;
        }
    }
}

void
data::DataRequest::arrangeActualNames() noexcept
{
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

void
data::DataRequest::arrangeColumns() noexcept
{
    if (mColumns.size() > 1)
    {
        bool flag = false;
        for (size_t i = 0; i < mColumns.size(); ++i)
        {
            if (mColumns[i].empty())
            {
                flag        = true;
                mColumns[i] = aTableColumns[mTables[i]];
            }
        }

        if (flag)
        {
            for (size_t i = 0; i < mPrev.size(); ++i)
            {
                mColumns[mPrev[i]].erase(mTables[i] + "_id");
            }
        }
    }
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
