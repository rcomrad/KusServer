#include "data_request.hpp"

#include "database_structures.hpp"

std::unordered_map<std::string, std::string> data::DataRequest::aTableNames = {
    {"methodist", "user"},
    {"teacher",   "user"}
};

data::TableInfo::TableInfo(std::string&& aTableName, int aParentNum) noexcept
    : tableName(std::move(aTableName)), parentNum(aParentNum)
{
    jsonName = tableName;
    int sz   = jsonName.size();
    if (jsonName[sz - 1] == 'd' && jsonName[sz - 2] == 'i' &&
        jsonName[sz - 3] == '_')
    {
        jsonName.resize(jsonName.size() - 3);
    }
}

data::TableInfo&
data::TableInfoAray::operator[](size_t num) noexcept
{
    return arr[num];
}

const std::string&
data::TableInfoAray::getCondition() const noexcept
{
    return mCondition;
}

std::optional<const std::string*>
data::TableInfoAray::popTableName() noexcept
{
    std::optional<const std::string*> result;
    if (mCnt < arr.size())
    {
        result = &arr[mCnt++].fullName;
    }
    return result;
}

data::DataRequest::DataRequest(const std::string& aRequest,
                               const std::string& aCondition) noexcept
    : curNum(0), last(0), iter(0), requestCellNum(0), brackets(0)
{
    for (iter = 0; iter < aRequest.size() + 1; ++iter)
    {
        switch (aRequest[iter])
        {
            case '[':
                newTable(aRequest);
                brackets++;
                break;

            case ']':
                pushName(aRequest);
                curNum = request[requestCellNum][curNum].parentNum;
                brackets--;
                break;

            case '\0':
            case ';':
                if (brackets == 0)
                {
                    newTable(aRequest);
                }
                else
                {
                    pushName(aRequest);
                }
                break;
        }
    }
    // pushName(aRequest);

    // for (auto& i : request)
    // {
    //     for (size_t j = 1; j < i.size(); ++j)
    //     {
    //         i[j].trueName = getTableName(
    //             i[j].tableName.substr(0, i[j].tableName.size() - 3));
    //     }
    // }
    // for (auto& i : request)
    // {
    //     i[0].trueName = getTableName(i[0].tableName);
    // }

    for (auto& i : request)
    {
        bool flag = true;
        for (auto& j : i)
        {
            if (flag)
            {
                j.trueName = getTableName(j.tableName);
                flag       = false;
            }
            else
            {
                j.trueName =
                    getTableName(j.tableName.substr(0, j.tableName.size() - 3));
            }

            if (j.rowNames.size() == 1 && j.rowNames.count("*") ||
                j.rowNames.size() == 0)
            {
                j.rowNames.clear();
                for (auto& k : AsteriskHendler::table[j.trueName])
                {
                    j.rowNames.insert(k);
                }
            }

            // for (size_t k = 0; k < AsteriskHendler::table[j.trueName].size();
            //      ++k)
            // {
            //     if (j.rowNames.count(AsteriskHendler::table[j.trueName][k]))
            //     {
            //         j.rowNumbers.emplace_back(k);
            //     }
            // }

            for (auto& i : j.rowNames)
            {
                for (size_t k = 0;
                     k < AsteriskHendler::table[j.trueName].size(); ++k)
                {
                    if (AsteriskHendler::table[j.trueName][k] == i)
                    {
                        j.rowNumbers.emplace_back(k);
                        break;
                    }
                }
            }

            // arr[0].fullName = aShame + "." + arr[0].trueName;
            j.fullName = "journal"s + "." + j.trueName;
        }
    }

    if (aCondition.size() == 0) return;
    curNum = 0;
    last   = 0;
    for (iter = 0; iter < aCondition.size() + 1; ++iter)
    {
        if (aCondition[iter] == ';' || aCondition[iter] == '\0')
        {
            if (curNum >= request.size()) break;

            request[curNum].mCondition += request[0][0].fullName + ".";
            request[curNum].mCondition += aCondition.substr(last, iter);
            last = iter + 1;

            curNum++;
        }
    }
}

std::string
data::TableInfoAray::getTables() const noexcept
{
    std::string result = arr[0].fullName + " ";
    for (size_t i = 1; i < arr.size(); ++i)
    {
        auto& temp = arr[i];
        result += "inner join " + temp.fullName + " on " +
                  arr[temp.parentNum].fullName + "." + temp.tableName + " = " +
                  temp.fullName + ".id ";
    }
    return result;
}

std::string
data::TableInfoAray::getColumns() noexcept
{
    std::string result;

    // int cnt = 0;
    for (auto& i : arr)
    {
        for (auto& j : i.rowNames)
        {
            result += i.fullName + "." + j + ", ";
            // i.rowNumbers.emplace_back(cnt++);
        }
    }

    if (!result.empty()) result.resize(result.size() - 2);

    // if (arr.size() == 1 && arr.rowNames.size() == 0)
    // {
    //     result = "*  ";
    // }
    // else
    // {
    //     for (auto& i : arr)
    //     {
    //         if (i.rowNames.size() == 1 && i.rowNames.count("*"))
    //         {
    //             for (auto& j : TableColumnNames::dict[i.trueName])
    //             {
    //                 result += j + ", ";
    //             }
    //         }
    //         else
    //         {
    //             for (auto& j : i.rowNames)
    //             {
    //                 result += j + ", ";
    //             }
    //         }
    //     }
    // }

    // result.resize(result.size() - 2);

    return result;
}

size_t
data::DataRequest::size() const noexcept
{
    return request.size();
}

void
data::DataRequest::pushName(const std::string& aRequest) noexcept
{
    if (iter - last > 1)
    {
        request[requestCellNum][curNum].rowNames.insert(
            aRequest.substr(last, iter - last));
    }
    last = iter + 1;
}

void
data::DataRequest::newTable(const std::string& aRequest) noexcept
{
    if (iter - last > 1)
    {
        if (brackets == 0)
        {
            request.emplace_back();
            requestCellNum = request.size() - 1;
        }
        request[requestCellNum].emplace_back(aRequest.substr(last, iter - last),
                                             curNum);
        curNum = request[requestCellNum].size() - 1;
    }
    last = iter + 1;
}
