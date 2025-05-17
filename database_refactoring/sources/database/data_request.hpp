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

class DataRequest
{
public:
    DataRequest(const std::string& aRequest, std::string&& aCondition) noexcept;

    std::string getTables() const noexcept;
    std::string getColumns() const noexcept;
    const std::string& getCondition() const noexcept;

    const std::string& getTableName(size_t aNum) const noexcept;
    std::string getNickname(size_t aNum) const noexcept;
    const std::unordered_set<std::string>& getTableColumns(
        size_t aNum) const noexcept;
    int getPreviousNum(size_t aNum) const noexcept;

    size_t size() const noexcept;

private:
    std::vector<int> mPrev;
    std::vector<std::string> mTables;
    std::vector<std::string> mNicknames;
    std::vector<std::unordered_set<std::string>> mColumns;
    std::string mCondition;

    static std::unordered_map<std::string, std::string> aTableNames;

    void pushTable(int iter,
                   int& last,
                   const std::string& aRequest,
                   int aOffset) noexcept;

    void pushName(int iter,
                  int& last,
                  const std::string& aRequest,
                  int curPrev) noexcept;
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATA_REQUEST_HPP
