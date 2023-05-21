#include "request_handler.hpp"

#include "file/file.hpp"

get::RequestHandler&
get::RequestHandler::getInstance() noexcept
{
    static RequestHandler instance;
    return instance;
}

std::unordered_map<std::string, std::string> get::RequestHandler::mTableNames =
    {
        {"methodist", "user"},
        {"teacher",   "user"}
};

std::unordered_map<std::string, std::unordered_map<std::string, int>>
    get::RequestHandler::mTableColumns = getTableColumns();

std::unordered_map<std::string, std::unordered_map<std::string, int>>
get::RequestHandler::getTableColumns() noexcept
{
    std::unordered_map<std::string, std::unordered_map<std::string, int>>
        result;

    auto words = file::File::getWords("database.psql_db", true);
    decltype(result.begin()) it;

    int cnt = 0;
    for (auto& i : words)
    {

        if (i[0] == "TABLE")
        {
            result[i[1]] = {
                {"id", 0}
            };
            it  = result.find(i[1]);
            cnt = 0;
            // it = result.insert(i[1], {"id"}).first;
        }
        else
        {
            it->second[i[0]] = cnt++;
            // it->second[i[0]] = it->second.size();
        }
    }

    return result;
}

Request
get::RequestHandler::processRequest(const std::string& aRequest,
                                    const std::string& aCondition) noexcept
{
    Request result;
    parseRequest(result, aRequest);
    makeTableNames(result);
    makeColumnNums(result);

    result.statement = getStatement();

    if (aCondition.size())
    {
        result.statement += " WHERE " + aCondition;
    }

    return result;
}

//--------------------------------------------------------------------------------

void
get::RequestHandler::parseRequest(Request& result,
                                  const std::string& aRequest) noexcept
{
    int curPrev = 0;
    int last    = 0;
    for (int iter = 0; iter < aRequest.size() + 1; ++iter)
    {
        switch (aRequest[iter])
        {
            case '[':
                result.previous.emplace_back(curPrev);
                curPrev = result.nicknames.size();
                pushTable(iter, last, aRequest, curPrev ? 3 : 0);
                break;

            case '\0':
                if (result.nicknames.empty())
                {
                    pushTable(iter, last, aRequest, 0);
                    break;
                }
            case ']':
            case ';':
                pushName(iter, last, aRequest, curPrev);
                if (aRequest[iter] == ']') curPrev = result.previous[curPrev];
                break;
        }
    }
}

void
get::RequestHandler::makeTableNames(Request& result) noexcept
{
    for (auto& i : result.nicknames)
    {
        auto it = mTableNames.find(i);
        if (it != mTableNames.end())
        {
            result.tableNames.emplace_back(it->second);
        }
        else
        {
            result.tableNames.emplace_back(i);
        }
    }
}

void
get::RequestHandler::makeColumnNums(Request& result) noexcept
{
    if (mColumns.size() > 1)
    {
        bool flag = false;
        for (size_t i = 0; i < result.columnNums.size(); ++i)
        {
            if (mColumns[i].empty())
            {
                flag = true;
                mColumns[i].insert(mTableColumns[mTables[i]]);
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
get::RequestHandler::makeColumnPart() const noexcept
{
    std::string result;

    return result;
}

std::string
get::RequestHandler::getStatement() const noexcept
{
    std::string result = "SELECT ";
    int sz             = result.size();

    //--------------------------------------------------------------------------------

    for (size_t i = 0; i < mColumns.size(); ++i)
    {
        for (auto& j : mColumns[i])
        {
            result += "journal." + mTables[i] + "." + std::to_string(j) + ", ";
        }
    }

    if (result.size() != sz)
    {
        result.resize(result.size() - 2);
    }
    else
    {
        result += "* ";
    }

    //--------------------------------------------------------------------------------

    result += "FROM journal." + mTables[0] + " ";
    for (size_t i = 1; i < mTables.size(); ++i)
    {
        result += "inner join journal." + mTables[i] + " on journal." +
                  mTables[mPrev[i]] + "." + mTables[i] + "_id" + " = journal." +
                  mTables[i] + ".id ";
    }

    return result;
}

//--------------------------------------------------------------------------------

void
get::RequestHandler::pushTable(int iter,
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
get::RequestHandler::pushName(int iter,
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
