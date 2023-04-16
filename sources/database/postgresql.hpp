#ifndef POSTGRESQL_HPP
#define POSTGRESQL_HPP

//--------------------------------------------------------------------------------

#include <cstring>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "domain/error_message.hpp"

#include "database_structures.hpp"

#include "boost/unordered_map.hpp"
#include "pqxx/pqxx"

#include "data_request.hpp"
#include "table.hpp"

//--------------------------------------------------------------------------------

namespace data
{

struct DBSettings
{
    std::string name;
    std::string user;
    std::string password;
    std::string shame;
};

class Postgresql
{
public:
    Postgresql(const DBSettings& aDBS);
    ~Postgresql() = default;

    Postgresql(const Postgresql& other)            = delete;
    Postgresql& operator=(const Postgresql& other) = delete;

    Postgresql(Postgresql&& other) noexcept            = default;
    Postgresql& operator=(Postgresql&& other) noexcept = default;

    // std::unordered_map<std::string, uint8_t> getColumnNames() noexcept;
    // std::vector<data::Type> getColumnTypes(
    //     const std::string& aTableName) noexcept;
    // std::unordered_map<std::string, uint8_t> getColumnNames(
    //     const std::string& aTableName) noexcept;

    //--------------------------------------------------------------------------------

    // TODO: aColums
    template <typename T>
    Table<T> select(const std::vector<std::string>& aColums = {},
                    const std::string& aConditon            = "") noexcept
    {
        Table<T> result;

        select(T::tableName, aColums, aConditon);

        while (true)
        {
            step();
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
        }

        closeStatment();

        return result;
    }

    int cnt = 0;
    // TODO: aColums
    template <typename T>
    Table<T> select2(const std::vector<int>& aColums = {},
                     const std::string& aConditon    = "") noexcept
    {
        Table<T> result;

        const std::vector<int>* colums = &aColums;
        std::vector<int> stock;
        // TODO: vector from table
        if (aColums.empty())
        {
            for (size_t i = 0; i < result.types.size(); ++i)
            {
                stock.emplace_back(i);
            }
            colums = &stock;
        }

        mResultIterator = --mResult.begin();
        while (true)
        {
            step();
            if (!hasData()) break;
            result.data.emplace_back();
            for (int i = 0; i < colums->size(); ++i)
            {
                auto num = cnt + i;
                if (!hasData(num)) break;
                auto ptr = result.back()[(*colums)[i]];

                switch (result.types[(*colums)[i]])
                {
                    case data::Type::INT:
                        *((int*)ptr) = getColumnIntUnsafe(num);
                        break;
                    case data::Type::BOOL:
                        *((bool*)ptr) = getColumnBoolUnsafe(num);
                        break;
                    case data::Type::CHARS:
                        strcpy((char*)ptr, getColumnAsCharsUnsafe(num));
                        break;
                    case data::Type::STRING:
                        *((std::string*)ptr) = getColumnAsStringUnsafe(num);
                        break;
                }
            }
        }
        if (!mMakeDBRequest) cnt += aColums.size();

        return result;
    }

    void handSelect(data::TableInfoAray& request) noexcept
    {
        auto tabl = request.getTables();
        auto col  = request.getColumns();
        auto con  = request.getCondition();

        std::string statement = "SELECT "s + col + " FROM " + tabl +
                                (con == "" ? "" : " WHERE ") + con;

        prepare({std::move(statement)});

        mMakeDBRequest = false;
    }

    void handClose() noexcept
    {
        closeStatment();
        cnt            = 0;
        mMakeDBRequest = true;
    }

    void select(const std::string& aTableName,
                const std::vector<std::string>& aColum = {},
                const std::string& aConditon           = "") noexcept;

    //--------------------------------------------------------------------------------

    int insert(const std::string& aTableName,
               const std::string& aData) noexcept;
    void update(const std::string& aTableName,
                const std::string& aData,
                const std::string& aConditon) noexcept;
    void drop(const std::string& aTableName,
              const std::string& aConditon) noexcept;
    //--------------------------------------------------------------------------------

    void createEnvironment(const DBSettings& aDBS) noexcept;
    void createTable(const std::string& aTableName,
                     const std::vector<ColumnSetting>& aColums) noexcept;
    void deleteDatabase(const std::string& aTableName,
                        const std::string& aUserName) noexcept;
                        
    //--------------------------------------------------------------------------------

    std::optional<int> getColumnInt(int aColumNumber) noexcept;
    std::optional<bool> getColumnBool(int aColumNumber) noexcept;
    std::optional<const char*> getColumnAsChars(int aColumNumber) noexcept;
    std::optional<std::string> getColumnAsString(int aColumNumber) noexcept;

    int getColumnIntUnsafe(int aColumNumber) noexcept;
    bool getColumnBoolUnsafe(int aColumNumber) noexcept;
    const char* getColumnAsCharsUnsafe(int aColumNumber) noexcept;
    std::string getColumnAsStringUnsafe(int aColumNumber) noexcept;

    //--------------------------------------------------------------------------------

private:
    std::unique_ptr<pqxx::connection> mConnection;
    std::unique_ptr<pqxx::work> mStatement;
    pqxx::result mResult;
    pqxx::result::const_iterator mResultIterator;

    //--------------------------------------------------------------------------------

    void step() noexcept;
    bool hasData(int num = 0) const noexcept;
    void closeStatment() noexcept;

    void prepare(const std::string& aStatment) noexcept;
    void exec(const std::string& aStatement) noexcept;
    void nontransaction(const std::string& aStatment) noexcept;

    //--------------------------------------------------------------------------------

    void createSequence(const std::string& aTableName) noexcept;

    bool mMakeDBRequest = true;
};
} // namespace data

//--------------------------------------------------------------------------------

#endif // !POSTGRESQL_HPP
