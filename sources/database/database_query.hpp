#ifndef DATABASE_QUERY_HPP
#define DATABASE_QUERY_HPP

//--------------------------------------------------------------------------------

#include <map>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "domain/string.hpp"

#include "postgresql.hpp"

//--------------------------------------------------------------------------------

namespace data
{
class DatabaseQuery
{
public:
    DatabaseQuery(const DBSettings& aDBS) noexcept;
    ~DatabaseQuery() = default;

    DatabaseQuery(const DatabaseQuery& other)            = delete;
    DatabaseQuery& operator=(const DatabaseQuery& other) = delete;

    DatabaseQuery(DatabaseQuery&& other) noexcept            = default;
    DatabaseQuery& operator=(DatabaseQuery&& other) noexcept = default;

    std::vector<data::User> getUser(const std::string& aLogin = "") noexcept;

    template <typename T>
    Table<T> getData(const std::string& aCondition = "") noexcept
    {
        return mDatabase.selectAll<T>({}, aCondition);
    }

    template <typename T>
    int insert(const Table<T>& aData) noexcept
    {
        return mDatabase.insert<T>(aData);
    }

    template <typename T>
    int update(const Table<T>& aData) noexcept
    {
        return mDatabase.update<T>(aData);
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

    // TODO: delete
    int insert(const std::string& aTableName,
               const std::vector<std::string>& aData) noexcept;

    void createTable(const std::string& aTableName,
                     const std::vector<ColumnSetting>& aColumns) noexcept;
    void createEnvironment(const DBSettings& aDBS) noexcept;
    void dropDatabase(const DBSettings& aDBS) noexcept;

    std::vector<data::Type> getColumnTypes(
        const std::string& aTableName) noexcept;
    std::unordered_map<std::string, uint8_t> getColumnNames(
        const std::string& aTableName) noexcept;


private:
    Postgresql mDatabase;
};
} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATABASE_QUERY_HPP
