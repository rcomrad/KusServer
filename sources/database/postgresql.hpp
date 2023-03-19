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

#include "data_request.hpp"

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

    std::unordered_map<std::string, uint8_t> getColumnNames() noexcept;

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

        while (true)
        {
            step();
            if (!hasData()) break;
            result.data.emplace_back();
            for (int i = 0; i < colums->size(); ++i)
            {
                auto ptr = result.back()[(*colums)[i]];
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

        return result;
    }

    // TODO: to database_query
    template <typename T>
    int update(Table<T>& aData) noexcept
    {
        int res = 0;

        for (int i = 0; i < aData.size(); ++i)
        {
            int& id = *((int*)aData[i][0]);
            if (id == 0)
                id = insertWithID(aData.getTableName(), id,
                                  aData.makeStrings(i, true, true));
            else
                update(aData.getTableName(), aData.makeStrings(i, false, true),
                       "id = " + wrap(id));
            res = id;
        }

        return res;
    }

    // TODO: to database_query
    // template <typename... Args>
    // void select(const data::TableInfoAray& request, Args&&... args) noexcept
    // {
    //     auto tabl = request.getTables();
    //     auto col  = request.getColumns();
    //     auto con  = request.getCondition();
    //     // if (columns.empty()) columns = "*";

    //     // std::vector<std::vector<int>> colNum;
    //     // for (auto& i : aDataRequest.request[aNum])
    //     // {
    //     //     ([&] { colNum.emplace_back(args.getColumnNums(i.rowNames));
    //     }(),
    //     //      ...);
    //     // }

    //     std::string statement = "SELECT "s + col + " FROM " + tabl +
    //                             (con == "" ? "" : " WHERE ") + con;

    //     prepare({std::move(statement)});

    //     while (true)
    //     {
    //         step();
    //         size_t cnt = 0;
    //         if (!hasData()) break;

    //         (
    //             [&]
    //             {
    //                 args.data.emplace_back();
    //                 for (auto i : request[cnt].rowNumbers)
    //                 {
    //                     auto ptr = args.back()[i];
    //                     if (!hasData(i)) break;
    //                     switch (args.types[i])
    //                     {
    //                         case data::Type::INT:
    //                             *((int*)ptr) = getColumnIntUnsafe(i);
    //                             break;
    //                         case data::Type::BOOL:
    //                             *((bool*)ptr) = getColumnBoolUnsafe(i);
    //                             break;
    //                         case data::Type::CHARS:
    //                             strcpy((char*)ptr,
    //                             getColumnAsCharsUnsafe(i)); break;
    //                         case data::Type::STRING:
    //                             *((std::string*)ptr) =
    //                                 getColumnAsStringUnsafe(i);
    //                             break;
    //                     }
    //                 }
    //                 cnt++;
    //             }(),
    //             ...);
    //     }

    //     closeStatment();
    // }

    void handSelect(const data::TableInfoAray& request) noexcept
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
        mMakeDBRequest = true;
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
    int insertWithID(const std::string& aTableName,
                     int id,
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

    // TODO: to database_query?
    std::string mShame;
    std::string mUser;
    std::string mDatabase;

    void prepare(const std::string& aStatment) noexcept;
    void exec(const std::vector<std::string>& aStatement) noexcept;
    void nontransaction(const std::string& aStatment) noexcept;

    void createSequence(const std::string& aTableName) noexcept;

    std::string merge(const std::vector<std::string>& aStrings);
    void merge(std::string& aResult, const std::vector<std::string>& aStrings);

    bool mMakeDBRequest = true;
};
} // namespace data

//--------------------------------------------------------------------------------

#endif // !POSTGRESQL_HPP
