#ifndef DATA_REQUEST_HPP
#define DATA_REQUEST_HPP

//--------------------------------------------------------------------------------

#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

//--------------------------------------------------------------------------------

namespace data
{
struct TableInfo
{
    std::string tableName;
    std::string trueName;
    std::string fullName;
    // std::unordered_set<std::string> rowNames;
    std::unordered_set<std::string> rowNames;
    std::vector<int> rowNumbers;
    int parantNum;

    TableInfo(std::string&& aTableName, int aParantNum) noexcept;
};

class TableInfoAray
{
public:
    std::string getTables() const noexcept;
    std::string getColumns() const noexcept;
    const std::string& getCondition() const noexcept;

    TableInfo& operator[](size_t num) noexcept;

    std::optional<const std::string*> popTableName() noexcept;

    auto begin() noexcept
    {
        return arr.begin();
    }
    auto end() noexcept
    {
        return arr.end();
    }

    auto begin() const noexcept
    {
        return arr.cbegin();
    }
    auto end() const noexcept
    {
        return arr.cend();
    }

private:
    std::vector<TableInfo> arr;
    std::string mCondition;
    size_t mCnt = 0;

    friend class DataRequest;

    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        arr.emplace_back(std::forward<Args>(args)...);
    }

    size_t size()
    {
        return arr.size();
    }
};

class DataRequest
{
public:
    DataRequest(const std::string& aRequest,
                const std::string& aCondition) noexcept;

    size_t size() const noexcept;

    auto begin() noexcept
    {
        return request.begin();
    }
    auto end() noexcept
    {
        return request.end();
    }

    auto begin() const noexcept
    {
        return request.cbegin();
    }
    auto end() const noexcept
    {
        return request.cend();
    }

private:
    std::vector<TableInfoAray> request;
    size_t curNum;
    size_t last;
    size_t iter;
    size_t requestCellNum;
    int brackets;

    static std::unordered_map<std::string, std::string> aTableNames;

    void pushName(const std::string& aRequest) noexcept;
    void newTable(const std::string& aRequest) noexcept;

    template <typename T>
    std::string getTableName(T&& aName) const noexcept
    {
        std::string result;
        auto it = aTableNames.find(aName);
        if (it != aTableNames.end())
        {
            aName = it->second;
        }
        else
        {
            result = std::forward<T>(aName);
        }
        return aName;
    }
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATA_REQUEST_HPP
