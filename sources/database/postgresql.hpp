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

#include "data_array.hpp"
#include "data_request.hpp"

//--------------------------------------------------------------------------------

namespace data
{

struct ColumnSetting
{
    std::string name;
    std::string type;
    std::string info;

    // For stupid GNU!
    ColumnSetting(std::string aName,
                  std::string aType,
                  std::string aInfo = "") noexcept;
};

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

    //--------------------------------------------------------------------------------

    void select(const std::string& aTableName,
                const std::string& aColum    = "",
                const std::string& aCondition = "") noexcept;

    std::string getCell(const std::string& aTableName,
                        const std::string& aColumnName,
                        const std::string& aCondition) noexcept;

    void closeStatment() noexcept;

    // TODO: aColums
    template <typename T>
    void getDataArray(DataArray<T>& result,
                      int& aOffset,
                      const std::unordered_set<int>& aColums = {},
                      bool aIsAutoClose                      = true) noexcept
    {
        mResultIterator = --mResult.begin();
        while (true)
        {
            T temp;
            auto flag = getData(temp, aOffset, aColums, false);
            // TODO: check move
            if (flag) result.emplace_back(std::move(temp));
            else break;
        }
        if (aIsAutoClose) closeStatment();
    }

    template <typename T>
    bool getData(T& result,
                 int& aOffset,
                 const std::unordered_set<int>& aColums = {},
                 bool aIsAutoClose                      = true) noexcept
    {
        bool res = false;
        step();
        if (hasData())
        {
            res = true;

            for (int i = 0; i < T::types.size(); ++i)
            {
                int num = aOffset + i;
                if (!hasData(num)) break;
                if (!aColums.empty() && !aColums.count(i)) continue;

                switch (T::types[i])
                {
                    case data::Type::INT:
                        *((int*)result.ptrs[i]) = getColumnIntUnsafe(num);
                        break;
                    case data::Type::BOOL:
                        *((bool*)result.ptrs[i]) = getColumnBoolUnsafe(num);
                        break;
                    case data::Type::STRING:
                        *((std::string*)result.ptrs[i]) =
                            getColumnAsStringUnsafe(num);
                        break;
                }
            }

            aOffset += aColums.size();
        }

        if (aIsAutoClose) closeStatment();
        return res;
    }

    //--------------------------------------------------------------------------------

    int insert(const std::string& aTableName,
               const std::string& aData) noexcept;
    void update(const std::string& aTableName,
                const std::string& aData,
                const std::string& aCondition) noexcept;
    void drop(const std::string& aTableName,
              const std::string& aCondition) noexcept;
    //--------------------------------------------------------------------------------

    void createEnvironment(const DBSettings& aDBS) noexcept;
    void createTable(const std::string& aTableName,
                     const std::vector<ColumnSetting>& aColums,
                     const std::string& aUserName) noexcept;
    void deleteDatabase(const std::string& aDBName) noexcept;

    //--------------------------------------------------------------------------------

    std::optional<int> getColumnInt(int aColumNumber) noexcept;
    std::optional<bool> getColumnBool(int aColumNumber) noexcept;
    std::optional<const char*> getColumnAsChars(int aColumNumber) noexcept;
    std::optional<std::string> getColumnAsString(int aColumNumber) noexcept;

    int getColumnIntUnsafe(int aColumNumber) noexcept;
    bool getColumnBoolUnsafe(int aColumNumber) noexcept;
    const char* getColumnAsCharsUnsafe(int aColumNumber) noexcept;
    std::string getColumnAsStringUnsafe(int aColumNumber) noexcept;

    std::string getRaw(int aColumNumber) noexcept;

    //--------------------------------------------------------------------------------

private:
    std::unique_ptr<pqxx::connection> mConnection;
    std::unique_ptr<pqxx::work> mStatement;
    pqxx::result mResult;
    pqxx::result::const_iterator mResultIterator;

    //--------------------------------------------------------------------------------

    void step() noexcept;
    bool hasData(int num = 0) const noexcept;

    void prepare(const std::string& aStatment) noexcept;
    void exec(const std::string& aStatement) noexcept;
    void nontransaction(const std::string& aStatment) noexcept;

    //--------------------------------------------------------------------------------

    void createSequence(const std::string& aTableName,
                        const std::string& aUserName) noexcept;
};
} // namespace data

//--------------------------------------------------------------------------------

#endif // !POSTGRESQL_HPP
