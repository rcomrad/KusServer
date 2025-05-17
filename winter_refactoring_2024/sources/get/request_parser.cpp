#include "request_parser.hpp"

#include "database/database_structures.hpp"

#include "text_data/file.hpp"
#include "get/get_router.hpp"

std::unordered_map<std::string, std::string> get::RequestParser::mActualNames =
    {
        {"methodist", "user"},
        {"teacher",   "user"},
        {"head",      "user"},
        {"student",   "user"}
};

const get::RequestParser::DataRequest::TableData&
get::RequestParser::DataRequest::operator[](int num) const noexcept
{
    return tables[num];
}

std::string
get::RequestParser::DataRequest::getFullStatement(
    const std::string& aCondition) const noexcept
{
    // TODO: auto schema
    return rowStatement +
           (aCondition.empty()
                ? ""
                : " WHERE journal." + tables[0].name + "." + aCondition);
}

get::RequestParser::DataRequest
get::RequestParser::process(const std::string& aRequest) noexcept
{
    RequestParser instance;

    instance.parse(aRequest);
    instance.arrangeActualNames();
    instance.arrangeColumns();

    DataRequest result;
    result.rowStatement =
        "SELECT " + instance.getColumns() + " FROM " + instance.getTables();

    result.size = instance.mColumnNames.size();
    for (size_t i = 0; i < result.size; ++i)
    {
        auto& temp = result.tables.emplace_back();
        if (instance.mPrev.size() > i) temp.prev = instance.mPrev[i];
        temp.name            = instance.mTables[i];
        temp.nickname        = instance.mNicknames[i];
        temp.columnNames     = instance.mColumnNames[i];
        temp.columnNums      = instance.mColumnNums[i];
        temp.additionalTable = instance.mAdditionalTable[i];
    }

    return result;
}

std::string
get::RequestParser::getTables() const noexcept
{
    std::string result = "journal." + mTables[0] + " ";
    for (size_t i = 1; i < mTables.size(); ++i)
    {
        result += "inner join journal." + mTables[i] + " on journal." +
                  mTables[mPrev[i]] + "." + mNicknames[i] + "_id" +
                  " = journal." + mTables[i] + ".id ";
    }
    return result;
}

std::string
get::RequestParser::getColumns() const noexcept
{
    std::string result;

    for (size_t i = 0; i < mColumnNames.size(); ++i)
    {
        for (auto& j : mColumnNames[i])
        {
            result += "journal." + mTables[i] + "." + j + ", ";
        }
    }

    if (!result.empty()) result.resize(result.size() - 2);

    return result;
}

void
get::RequestParser::parse(const std::string& aRequest) noexcept
{
    int curPrev     = 0;
    int last        = 0;
    int parentheses = 0;
    for (int iter = 0; iter < aRequest.size() + 1; ++iter)
    {
        switch (aRequest[iter])
        {
            case '[':
                mPrev.emplace_back(curPrev);
                curPrev = mNicknames.size();
                pushTable(iter, last, aRequest, curPrev ? 3 : 0);
                break;

            case '(':
                last = iter + 1;

                ++parentheses;
                while (parentheses != 0)
                {
                    ++iter;
                    if (aRequest[iter] == '(') ++parentheses;
                    if (aRequest[iter] == ')') --parentheses;
                }

                mAdditionalTable[curPrev] = aRequest.substr(last, iter - last);

                last = iter;
                break;

            case ')':
            case '\0':
                if (mNicknames.empty())
                {
                    pushTable(iter, last, aRequest, 0);
                    break;
                }
            case ']':
            case ',':
                pushName(iter, last, aRequest, curPrev);
                if (aRequest[iter] == ']') curPrev = mPrev[curPrev];
                break;
        }
    }
}

void
get::RequestParser::arrangeActualNames() noexcept
{
    for (auto& i : mNicknames)
    {
        auto it = mActualNames.find(i);
        if (it != mActualNames.end())
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
get::RequestParser::arrangeColumns() noexcept
{
    std::vector<std::unordered_set<std::string>> uniqueNames;
    for (size_t i = 0; i < mColumnNames.size(); ++i)
    {
        auto& column = uniqueNames.emplace_back(mColumnNames[i].begin(),
                                                mColumnNames[i].end());
        if (column.empty() && mHasAttachment[i])
        {
            column.insert("-1");
        }
        else if (column.empty() || column.count("*"))
        {
            auto& temp = get::GetRouter::columnNamesRouter(mTables[i]);
            column = std::unordered_set<std::string>(temp.begin(), temp.end());
        }
    }

    for (size_t i = 0; i < mPrev.size(); ++i)
    {
        uniqueNames[mPrev[i]].erase(mNicknames[i] + "_id");
    }

    for (size_t i = 0; i < mColumnNames.size(); ++i)
    {
        mColumnNums.emplace_back();
        mColumnNames[i].clear();
        auto& temp = get::GetRouter::columnNamesRouter(mTables[i]);

        if (uniqueNames[i].count("-1"))
        {
            mColumnNums.back().insert(-1);
        }
        else
        {
            for (size_t j = 0; j < temp.size(); ++j)
            {
                if (uniqueNames[i].count(temp[j]))
                {
                    mColumnNums.back().insert(j);
                    mColumnNames[i].emplace_back(temp[j]);
                }
            }
        }
    }
}

void
get::RequestParser::pushTable(int iter,
                              int& last,
                              const std::string& aRequest,
                              int aOffset) noexcept
{
    if (iter - last > 1)
    {
        mColumnNames.emplace_back();
        // mAdditionalTable.emplace_back(nullptr);
        mAdditionalTable.emplace_back();
        if (!mHasAttachment.empty()) mHasAttachment.back() = true;
        mHasAttachment.emplace_back(false);
        mNicknames.emplace_back(aRequest.substr(last, iter - last - aOffset));
    }
    last = iter + 1;
}

void
get::RequestParser::pushName(int iter,
                             int& last,
                             const std::string& aRequest,
                             int curPrev) noexcept
{
    if (iter - last >= 1)
    {
        mColumnNames[curPrev].emplace_back(aRequest.substr(last, iter - last));
    }
    last = iter + 1;
}
