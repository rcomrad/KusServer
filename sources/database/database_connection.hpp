#ifndef DATABASE_CONNECTION_HPP
#define DATABASE_CONNECTION_HPP

//--------------------------------------------------------------------------------

#include <map>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

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

    template <typename T>
    DataArray<T> complexSelect(data::TableInfoAray& request) noexcept
    {
        mColumnNumber = 0;
        auto tabl     = request.getTables();
        auto col      = request.getColumns();
        auto con      = request.getCondition();
        mDatabase.select(tabl, col, con);
    }

    template <typename T>
    DataArray<T> getNextDataArray(
        const std::unordered_set<std::string>& aColumnNames = {}) noexcept
    {
        DataArray<T> result;
        std::unordered_set<std::string> columnNums;
        for (auto& i : aColumnNames)
        {
            columnNums.insert(T::columnNames[i]);
        }
        mDatabase.getDataArray<T>(result, mColumnNumber, columnNums);
        return result;
    }

    template <typename T>
    DataArray<T> getDataArray(
        const std::string& aCondition                       = "",
        const std::unordered_set<std::string>& aColumnNames = {}) noexcept
    {
        DataArray<T> result;
        auto columnNums = launchSelect(aCondition, aColumnNames);
        mDatabase.getDataArray(result, mColumnNumber, columnNums);
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
    T getData(const std::string& aCondition                       = "",
              const std::unordered_set<std::string>& aColumnNames = {}) noexcept
    {

        T result;
        auto columnNums = launchSelect(aCondition, aColumnNames);
        mDatabase.getData(result, mColumnNumber, columnNums);
        return result;
    }

    //--------------------------------------------------------------------------------

    template <typename T>
    int writeData(T& aData) noexcept
    {
        int res = 0;
        if (aData.id == 0)
        {
            res = insertData(aData);
        }
        else
        {
            res = updateData(aData);
        }
        return res;
    }

    template <typename T>
    int insertData(T& aData) noexcept
    {
        aData.id = mDatabase.insert(getTableName<T>(), aData.getAsInsert());
        return aData.id;
    }

    template <typename T>
    int updateData(const T& aData, const std::string& aConditon = "") noexcept
    {
        int res = 0;
        if (aData.id != 0)
        {
            mDatabase.update(getTableName<T>(), aData.getAsUpdate(),
                             aConditon.size() ? aConditon
                                              : data::wrap(aData.id));
            res = aData.id;
        }
        return res;
    }

    template <typename T>
    int dropData(T& aData) noexcept
    {
        int res = 0;
        if (aData.id != 0)
        {
            mDatabase.drop(getTableName<T>(), aData.getAsCondition());
            res = 1;
        }
        return res;
    }

    template <typename T>
    int dropByID(const std::vector<int>& aIDs) noexcept
    {
        int res = 0;
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

    // template <typename T>
    // int writeTable(Table<T>& aData) noexcept
    // {
    //     int res = 0;
    //     if (aData.size() > 0)
    //     {
    //         res = insert(aData);
    //     }
    //     else
    //     {
    //         res = update(aData);
    //     }
    //     return res;
    // }

    // template <typename T>
    // int insertTable(Table<T>& aData) noexcept
    // {
    //     int res = 0;
    //     if (aData.size())
    //     {
    //         res = mDatabase.insert(getTableName<T>(),
    //         aData.getAllAsInsert()); aData[0].id = res;
    //     }
    //     return res;
    // }

    // template <typename T>
    // int updateTable(const Table<T>& aData,
    //                 const std::string& aConditon = "") noexcept
    // {
    //     int res = 0;
    //     if (aData.size())
    //     {
    //         res = mDatabase.update(getTableName<T>(),
    //         aData.getFirstAsUpdate(),
    //                                aConditon.size() ? aConditon
    //                                                 :
    //                                                 data::wrap(aData[0].id));
    //     }
    //     return res;
    // }

    // template <typename T>
    // int dropTable(const Table<T>& aData) noexcept
    // {
    //     int res = 0;
    //     if (aData.size())
    //     {
    //         mDatabase.drop(getTableName<T>(), aData.getFirstAsCondition());
    //         res = 1;
    //     }
    //     return res;
    // }

    //--------------------------------------------------------------------------------

    void createTable(const std::string& aTableName,
                     const std::vector<ColumnSetting>& aColumns) noexcept;
    void createEnvironment(const ConnectionType& aType) noexcept;
    void dropDatabase(const ConnectionType& aType) noexcept;

    //--------------------------------------------------------------------------------

private:
    DBSettings mDBSettings;
    Postgresql mDatabase;

    int mColumnNumber;

    static std::unordered_map<ConnectionType, data::DBSettings>
        mConnectionTypeSettings;

    static std::unordered_map<ConnectionType, data::DBSettings>
    getConnectionTypeSettings() noexcept;

    template <typename T>
    std::string getTableName() const noexcept
    {
        return mDBSettings.shame + "." + T::tableName;
    }

    template <typename T>
    std::unordered_set<std::string> launchSelect(
        const std::string& aCondition,
        const std::unordered_set<std::string>& aColumnNames) noexcept
    {
        mColumnNumber = 0;
        std::string columns;
        std::unordered_set<std::string> result;
        for (auto& i : aColumnNames)
        {
            columns += i;
            result.insert(T::columnNames[i]);
        }
        mDatabase.select(getTableName<T>(), columns, aCondition);
        return result;
    }
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATABASE_CONNECTION_HPP
