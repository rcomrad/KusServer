#ifndef DATABASE_CONNECTION_HPP
#define DATABASE_CONNECTION_HPP

//--------------------------------------------------------------------------------

#include <map>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "domain/log.hpp"
#include "domain/metaprogramming.hpp"

#include "postgresql.hpp"

//--------------------------------------------------------------------------------

namespace data
{

enum class ConnectionType
{
    ADMIN,
    USER
};

class DatabaseConnection
{
public:
    DatabaseConnection(const DBSettings& aDBS) noexcept;
    DatabaseConnection(const ConnectionType& aType) noexcept;
    ~DatabaseConnection() = default;

    DatabaseConnection(const DatabaseConnection& other)            = delete;
    DatabaseConnection& operator=(const DatabaseConnection& other) = delete;

    DatabaseConnection(DatabaseConnection&& other) noexcept = default;
    DatabaseConnection& operator=(DatabaseConnection&& other) noexcept =
        default;

    //--------------------------------------------------------------------------------

    void complexSelect(const char* aRequest) noexcept;

    template <typename T>
    DataArray<T> getNextDataArray(
        const std::unordered_set<int>& aColumnNums = {}) noexcept
    {
        DataArray<T> result;
        mDatabase.getDataArray<T>(result, mColumnNumber, aColumnNums, false);
        // TODO close
        return result;
    }

    template <typename T>
    DataArray<T> getDataArray(
        const std::unordered_set<str::String>& aColumnNames) noexcept
    {
        return getDataArray<T>("", aColumnNames);
    }

    template <typename T>
    DataArray<T> getDataArray(
        const char* aCondition                              = "",
        const std::unordered_set<str::String>& aColumnNames = {}) noexcept
    {
        DataArray<T> result;
        auto columnNums = launchSelect<T>(aCondition, aColumnNames);
        mDatabase.getDataArray<T>(result, mColumnNumber, columnNums);
        return result;
    }

    // template <typename T>
    // void updateTable(
    //     Table<T>& result,
    //     const char* aCondition                       = "",
    //     const std::unordered_set<str::String>& aColumnNames = {}) noexcept
    // {
    //     auto columnNums = launchSelect(aCondition, aColumnNames);
    //     mDatabase.getTable(result, mColumnNumber, columnNums);
    // }

    template <typename T>
    T getData(const std::unordered_set<str::String>& aColumnNames) noexcept
    {
        return getData<T>("", aColumnNames);
    }

    template <typename T>
    T getData(const char* aCondition                              = "",
              const std::unordered_set<str::String>& aColumnNames = {}) noexcept
    {

        T result;
        auto columnNums = launchSelect<T>(aCondition, aColumnNames);
        mDatabase.getData(result, mColumnNumber, columnNums);
        return result;
    }

    //--------------------------------------------------------------------------------

    template <typename T,
              typename = dom::enableIfDerivedOf<data::BaseDataDummy, T>>
    int write(T& aData) noexcept
    {
        int res = -1;
        if (aData.id == 0)
        {
            res = insert(aData);
        }
        else
        {
            res = update(aData);
        }
        return res;
    }

    template <typename T,
              typename = dom::enableIfDerivedOf<data::BaseDataDummy, T>>
    int insert(T& aData) noexcept
    {
        auto temp = mDatabase.insert(getTableName<T>(), aData.getAsInsert());
        if (!temp.empty())
        {
            aData.id = temp[0];
        }
        else
        {
            LOG_ERROR("Insert", T::geName(), "element failed");
        }
        return aData.id;
    }

    template <typename T,
              typename = dom::enableIfDerivedOf<data::BaseDataDummy, T>>
    int update(const T& aData, const char* aCondition = "") noexcept
    {
        int res = -1;
        if (aData.id != 0)
        {
            mDatabase.update(getTableName<T>(), aData.getAsUpdate(),
                             aCondition.size() ? aCondition
                                               : "id=" + data::wrap(aData.id));
            res = aData.id;
        }
        return res;
    }

    int drop(const char* aTableName, const char* aCondition) noexcept;

    template <typename T,
              typename = dom::enableIfDerivedOf<data::BaseDataDummy, T>>
    int drop(T& aData) noexcept
    {
        mDatabase.drop(getTableName<T>(), aData.getAsCondition());
        // TODO: result
        return 1;
    }

    int dropByID(const char* aTableName, const std::vector<int>& aIDs) noexcept;

    //--------------------------------------------------------------------------------

    template <typename T>
    std::vector<int> write(DataArray<T>& aData) noexcept
    {
        std::vector<int> res;
        if (aData.size() > 0)
        {
            if (aData[0].id == 0)
            {
                res = insert(aData);
            }
            else
            {
                res = update(aData);
            }
        }
        return res;
    }

    template <typename T>
    std::vector<int> insert(DataArray<T>& aData) noexcept
    {
        auto res = mDatabase.insert(getTableName<T>(), aData.getAsInsert());
        for (int i = 0; i < res.size(); ++i)
        {
            aData[i].id = res[i];
        }
        return res;
    }

    template <typename T>
    std::vector<int> update(const DataArray<T>& aData,
                            const char* aCondition = "") noexcept
    {
        // TODO:
        std::vector<int> res = {-2};
        for (auto& i : aData)
        {
            update(i, aCondition);
        }
        return res;
    }

    template <typename T>
    int drop(const DataArray<T>& aData) noexcept
    {
        int res = aData.size();
        for (auto& i : aData)
        {
            drop(i);
        }
        return res;
    }

    //--------------------------------------------------------------------------------

    void createTable(const char* aTableName,
                     const std::vector<ColumnSetting>& aColumns) noexcept;
    void createEnvironment(const ConnectionType& aType) noexcept;
    void dropDatabase(const ConnectionType& aType) noexcept;

    //--------------------------------------------------------------------------------

    static bool securityCheck(const char* aStr) noexcept;

    //--------------------------------------------------------------------------------

    str::String getCell(const char* aTableName,
                        const char* aColumnName,
                        const char* aCondition) noexcept;

    //--------------------------------------------------------------------------------

private:
    DBSettings mDBSettings;
    Postgresql mDatabase;

    int mColumnNumber;

    static std::unordered_map<ConnectionType, data::DBSettings>
    generateConnectionTypeSettings() noexcept;
    static data::DBSettings getConnectionTypeSettings(
        const ConnectionType& aType) noexcept;

    str::String getTableName(const char* aTableName) const noexcept;
    template <typename T>
    str::String getTableName() const noexcept
    {
        return getTableName(T::tableName);
    }

    template <typename T>
    std::unordered_set<int> launchSelect(
        const char* aCondition,
        const std::unordered_set<str::String>& aColumnNames) noexcept
    {
        mColumnNumber = 0;
        str::String columns;
        std::unordered_set<int> result;
        for (auto& i : aColumnNames)
        {
            columns += i;
            result.insert(T::nameToNum[i]);
        }
        mDatabase.select(getTableName<T>(), columns, aCondition);
        return result;
    }
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATABASE_CONNECTION_HPP
