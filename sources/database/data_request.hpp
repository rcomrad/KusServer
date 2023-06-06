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

class RequestParser
{
private:
    struct DataRequest
    {
    private:
        struct TableData
        {
            int prev;
            std::string name;
            std::string nickname;
            std::unordered_set<std::string> columns;
        };

    public:
        size_t size;
        std::string statement;
        std::vector<TableData> tables;
    };

public:
    RequestParser() noexcept = default;
    DataRequest process(const std::string& aRequest,
                        const std::string& aCondition) noexcept;

private:
    std::vector<int> mPrev;
    std::vector<std::string> mTables;
    std::vector<std::string> mNicknames;
    std::vector<std::unordered_set<std::string>> mColumns;

    static std::unordered_map<std::string, std::string> mActualNames;

    std::string getTables() const noexcept;
    std::string getColumns() const noexcept;

    void parse(const std::string& aRequest) noexcept;
    void arrangeActualNames() noexcept;
    void arrangeColumns() noexcept;

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
