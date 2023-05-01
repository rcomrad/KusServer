#ifndef DATABASE_CONNECTION_HPP
#define DATABASE_CONNECTION_HPP

//--------------------------------------------------------------------------------

#include <map>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

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

    void complexSelect(const data::DataRequest& request) noexcept;

    template <typename T>
    DataArray<T> getNextDataArray(
        const std::unordered_set<std::string>& aColumnNames = {}) noexcept
    {
        DataArray<T> result;
        std::unordered_set<int> columnNums;
        for (auto& i : aColumnNames)
        {
            columnNums.insert(T::nameToNum[i]);
        }
        mDatabase.getDataArray<T>(result, mColumnNumber, columnNums, false);
        // TODO close
        return result;
    }

    template <typename T>
    DataArray<T> getDataArray(
        const std::unordered_set<std::string>& aColumnNames) noexcept
    {
        return getDataArray<T>("", aColumnNames);
    }

    template <typename T>
    DataArray<T> getDataArray(
        const std::string& aCondition                       = "",
        const std::unordered_set<std::string>& aColumnNames = {}) noexcept
    {
        DataArray<T> result;
        auto columnNums = launchSelect<T>(aCondition, aColumnNames);
        mDatabase.getDataArray<T>(result, mColumnNumber, columnNums);
        return result;
    }

    // template <typename T>
    // void updateTable(
    //     Table<T>& result,
    //     const std::string& aCondition                       = "",
    //     const std::unordered_set<std::string>& aColumnNames = {}) noexcept
    // {
    //     auto columnNums = launchSelect(aCondition, aColumnNames);
    //     mDatabase.getTable(result, mColumnNumber, columnNums);
    // }

    template <typename T>
    T getData(const std::unordered_set<std::string>& aColumnNames) noexcept
    {
        return getData<T>("", aColumnNames);
    }

    template <typename T>
    T getData(const std::string& aCondition                       = "",
              const std::unordered_set<std::string>& aColumnNames = {}) noexcept
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
        aData.id = mDatabase.insert(getTableName<T>(), aData.getAsInsert());
        return aData.id;
    }

    template <typename T,
              typename = dom::enableIfDerivedOf<data::BaseDataDummy, T>>
    int update(const T& aData, const std::string& aConditon = "") noexcept
    {
        int res = -1;
        if (aData.id != 0)
        {
            mDatabase.update(getTableName<T>(), aData.getAsUpdate(),
                             aConditon.size() ? aConditon
                                              : "id=" + data::wrap(aData.id));
            res = aData.id;
        }
        return res;
    }

    template <typename T,
              typename = dom::enableIfDerivedOf<data::BaseDataDummy, T>>
    int drop(T& aData) noexcept
    {
        mDatabase.drop(getTableName<T>(), aData.getAsCondition());
        // TODO: result
        return 1;
    }

    template <typename T>
    int dropByID(const std::vector<int>& aIDs) noexcept
    {
        int res = -1;
        if (aIDs.size())
        {
            auto name = getTableName<T>();
            for (auto i : aIDs)
            {
                mDatabase.drop(name, "id=" + data::wrap(i));
            }
            res = 1;
        }
        return res;
    }

    //--------------------------------------------------------------------------------

    template <typename T>
    int write(DataArray<T>& aData) noexcept
    {
        int res = 0;
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
    int insert(DataArray<T>& aData) noexcept
    {
        // TODO: id's?
        int res = aData.size();
        mDatabase.insert(getTableName<T>(), aData.getAsInsert());
        return res;
    }

    template <typename T>
    int update(const DataArray<T>& aData,
               const std::string& aConditon = "") noexcept
    {
        int res = aData.size();
        for (auto& i : aData)
        {
            update(i, aConditon);
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

    void createTable(const std::string& aTableName,
                     const std::vector<ColumnSetting>& aColumns) noexcept;
    void createEnvironment(const ConnectionType& aType) noexcept;
    void dropDatabase(const ConnectionType& aType) noexcept;

    //--------------------------------------------------------------------------------

    static bool securityCheck(const std::string& aStr) noexcept;

    //--------------------------------------------------------------------------------

    std::string getCell(const std::string& aTableName,
                        const std::string& aColumnName,
                        const std::string& aCondition) noexcept;

    //--------------------------------------------------------------------------------

private:
    DBSettings mDBSettings;
    Postgresql mDatabase;

    int mColumnNumber;

    static std::unordered_map<ConnectionType, data::DBSettings>
    generateConnectionTypeSettings() noexcept;
    static data::DBSettings getConnectionTypeSettings(
        const ConnectionType& aType) noexcept;

    std::string getTableName(const std::string& aTableName) const noexcept;
    template <typename T>
    std::string getTableName() const noexcept
    {
        return getTableName(T::tableName);
    }

    template <typename T>
    std::unordered_set<int> launchSelect(
        const std::string& aCondition,
        const std::unordered_set<std::string>& aColumnNames) noexcept
    {
        mColumnNumber = 0;
        std::string columns;
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
