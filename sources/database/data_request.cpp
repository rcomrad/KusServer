#include "data_request.hpp"

#include "database_structures.hpp"

#include "file/file.hpp"

std::unordered_map<std::string, std::string> data::DataRequest::aTableNames = {
    {"methodist", "user"},
    {"teacher",   "user"}
};

std::unordered_map<std::string, std::unordered_set<std::string>>
    data::DataRequest::aTableColumns = getTableColumns();

std::unordered_map<std::string, std::unordered_set<std::string>>
data::DataRequest::getTableColumns() noexcept
{
    std::unordered_map<std::string, std::unordered_set<std::string>> result;

    auto words = file::File::getWords("database.psql_db", true);
    std::unordered_map<std::string, std::unordered_set<std::string>>::iterator
        it;

    for (auto& i : words)
    {
        if (i[0] == "TABLE")
        {
            result[i[1]] = {"id"};
            it           = result.find(i[1]);
            // it = result.insert(i[1], {"id"}).first;
        }
        else
        {
            it->second.insert(i[0]);
        }
    }

    return result;
}

data::DataRequest::DataRequest(const std::string& aRequest,
                               std::string&& aCondition) noexcept
{
    mCondition = std::move(aCondition);

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
