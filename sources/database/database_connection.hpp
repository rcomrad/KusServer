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
    Table<T> getData(const std::string& aCondition = "") noexcept
    {
        return mDatabase.select<T>({}, aCondition);
    }

    template <typename T, typename... Args>
    Table<T> select(Args&&... args) noexcept
    {
        return mDatabase.select<T>(args...);
    }

    template <typename T, typename... Args>
    Table<T> select2(Args&&... args) noexcept
    {
        return mDatabase.select2<T>(args...);
    }

    void handSelect(data::TableInfoAray& request) noexcept
    {
        mDatabase.handSelect(request);
    }

    void handClose() noexcept
    {
        mDatabase.handClose();
    }

    template <typename T>
    int write(Table<T>& aData) noexcept
    {
        int res = 0;

        int& id = *((int*));
        if (id == 0)
            id = insertWithID(aData.getTableName(), id,
                              aData.makeStrings(i, true, true));
        else
            update(aData.getTableName(), aData.makeStrings(i, false, true),
                   "id = " + wrap(id));
        res = id;

        return res;
    }

    //--------------------------------------------------------------------------------

    template <typename T>
    int insert(const Table<T>& aData) noexcept
    {
        return mDatabase.insert(aData.getTableName(), aData);
    }

    template <typename T>
    void drop(const Table<T>& aData) noexcept
    {
        for (int i = 0; i < aData.size(); ++i)
        {
            mDatabase.drop(T::tableName, aData.getCondition(i));
        }
    }

    template <typename T>
    void dropByID(const std::vector<int>& aIDs) noexcept
    {
        mDatabase.dropByID(T::tableName, aIDs);
    }

    void createTable(const std::string& aTableName,
                     const std::vector<ColumnSetting>& aColumns) noexcept;
    void createEnvironment(const ConnectionType& aType) noexcept;
    void dropDatabase(const ConnectionType& aType) noexcept;

    //--------------------------------------------------------------------------------

    // std::vector<data::Type> getColumnTypes(
    //     const std::string& aTableName) noexcept;
    // std::unordered_map<std::string, uint8_t> getColumnNames(
    //     const std::string& aTableName) noexcept;

private:
    Postgresql mDatabase;

    // TODO: to database_query?
    std::string mShame;
    std::string mUser;
    std::string mDatabase;

    static std::unordered_map<ConnectionType, data::DBSettings>
        mConnectionTypeSettings;

    static std::unordered_map<ConnectionType, data::DBSettings>
    getConnectionTypeSettings() noexcept;
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATABASE_CONNECTION_HPP
