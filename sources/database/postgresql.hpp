#ifndef POSTGRESQL_HPP
#define POSTGRESQL_HPP

//--------------------------------------------------------------------------------

#include <cstring>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "domain/any.hpp"
#include "domain/error_message.hpp"
#include "domain/string.hpp"

#include "database_structures.hpp"

#include "boost/unordered_map.hpp"
#include "pqxx/pqxx"

//--------------------------------------------------------------------------------

namespace data
{
// using RowArray = std::vector<std::unordered_map<std::string, dom::Any>>;
using RowArray =
    std::vector<boost::unordered::unordered_map<std::string, dom::Any>>;
class Postgresql
{
public:
    Postgresql(const DBSettings& aDBS) noexcept;
    ~Postgresql() = default;

    Postgresql(const Postgresql& other)            = delete;
    Postgresql& operator=(const Postgresql& other) = delete;

    Postgresql(Postgresql&& other) noexcept            = default;
    Postgresql& operator=(Postgresql&& other) noexcept = default;

    // RowArray selectAll(const std::string& aTableName,
    //                    const std::vector<std::string>& aColums   = {},
    //                    const std::vector<std::string>& aConditon = {})
    //                    noexcept;

    std::unordered_map<std::string, uint8_t> getColumnNames() noexcept;

    template <typename T>
    Table<T> selectAll(const std::vector<std::string>& aColums = {},
                       const std::string& aConditon            = "") noexcept
    {
        Table<T> result;

        select(T::tableName, aColums, aConditon);
        step();

        while (true)
        {
            // std::cout << "SUS!\n";
            if (!hasData()) break;
            result.data.emplace_back();
            for (size_t i = 0; i < result.types.size(); ++i)
            {
                auto ptr = result.back()[i];
                if (!hasData(i)) break;
                switch (result.types[i])
                {
                    case data::Type::INT:
                        *((int*)ptr) = getColumnIntUnsafe(i);
                        break;
                    case data::Type::BOOL:
                        *((bool*)ptr) = getColumnBoolUnsafe(i);
                        break;
                    case data::Type::CHARS:
                        strcpy((char*)ptr, getColumnAsCharsUnsafe(i));
                        break;
                    case data::Type::STRING:
                        *((std::string*)ptr) = getColumnAsStringUnsafe(i);
                        break;
                }
            }
            step();
        }
        closeStatment();

        return result;
    }

    template <typename T>
    int insert(Table<T>& aData) noexcept
    {
        // TODO: normal return
        int res = 0;
        for (int i = 0; i < aData.size(); ++i)
        {
            int& id = *((int*)aData[i][0]);
            id      = insertWithID(aData.getTableName(), id,
                                   aData.makeStrings(i, true, true));
        }
        return res;
    }

    template <typename T>
    int update(const Table<T>& aData) noexcept
    {
        int res = 0;

        for (int i = 0; i < aData.size(); ++i)
        {
            int id = res = *((int*)aData[i][0]);
            if (id == 0)
                res = insertWithID(aData.getTableName(), id,
                                   aData.makeStrings(i, true, true));
            else
                update(aData.getTableName(), aData.makeStrings(i, false, true),
                       "id = " + wrap(id));
        }

        return res;
    }

    std::vector<data::Type> getColumnTypes(
        const std::string& aTableName) noexcept;
    std::unordered_map<std::string, uint8_t> getColumnNames(
        const std::string& aTableName) noexcept;

    void select(const std::string& aTableName,
                const std::vector<std::string>& aColum = {},
                const std::string& aConditon           = "") noexcept;
    int insert(const std::string& aTableName,
               const std::vector<std::string>& aData) noexcept;
    int insertWithID(const std::string& aTableName, int id,
                     const std::vector<std::string>& aData) noexcept;
    void update(const std::string& aTableName,
                const std::vector<std::string>& aValue,
                const std::string& aConditon) noexcept;
    void drop(const std::string& aTableName,
              const std::string& aConditon) noexcept;
    void dropByID(const std::string& aTableName,
                  const std::vector<int>& aIDs) noexcept;

    void createEnvironment(const DBSettings& aDBS) noexcept;
    void createTable(const std::string& aTableName,
                     const std::vector<ColumnSetting>& aColums) noexcept;
    void deleteDatabase(const std::string& aTableName) noexcept;

    void step() noexcept;
    bool hasData(int num = 0) const noexcept;
    void closeStatment() noexcept;

    std::optional<int> getColumnInt(int aColumNumber) noexcept;
    std::optional<bool> getColumnBool(int aColumNumber) noexcept;
    std::optional<const char*> getColumnAsChars(int aColumNumber) noexcept;
    std::optional<std::string> getColumnAsString(int aColumNumber) noexcept;

    int getColumnIntUnsafe(int aColumNumber) noexcept;
    bool getColumnBoolUnsafe(int aColumNumber) noexcept;
    const char* getColumnAsCharsUnsafe(int aColumNumber) noexcept;
    std::string getColumnAsStringUnsafe(int aColumNumber) noexcept;

private:
    std::unique_ptr<pqxx::connection> mConnection;
    std::unique_ptr<pqxx::work> mStatement;
    pqxx::result mResult;
    pqxx::result::const_iterator mResultIterator;

    std::string mShame;
    std::string mUser;
    std::string mDatabase;

    void prepare(const std::string& aStatment) noexcept;
    void exec(const std::vector<std::string>& aStatement) noexcept;
    void nontransaction(const std::string& aStatment) noexcept;

    void createSequence(const std::string& aTableName) noexcept;

    std::string merge(const std::vector<std::string>& aStrings);
    void merge(std::string& aResult, const std::vector<std::string>& aStrings);
};
} // namespace data

//--------------------------------------------------------------------------------

#endif // !POSTGRESQL_HPP
