#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

//--------------------------------------------------------------------------------

// #include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

//--------------------------------------------------------------------------------

namespace get
{

class RequestParser
{
public:
    struct DataRequest
    {
    private:
        struct TableData
        {
            int prev;
            std::string name;
            std::string nickname;
            std::unordered_set<int> columnNums;
            std::vector<std::string> columnNames;
            // std::unique_ptr<DataRequest*> additionalTable;
            std::string additionalTable;
        };

    public:
        size_t size;
        std::string rowStatement;
        std::vector<TableData> tables;

        const TableData& operator[](int num) const noexcept;
        std::string getFullStatement(
            const std::string& aCondition) const noexcept;
    };

    static DataRequest process(const std::string& aRequest) noexcept;

private:
    std::vector<int> mPrev;
    std::vector<std::string> mTables;
    std::vector<std::string> mNicknames;
    std::vector<std::unordered_set<int>> mColumnNums;
    std::vector<std::vector<std::string>> mColumnNames;
    std::vector<bool> mHasAttachment;
    // std::vector<std::unique_ptr<DataRequest>> mAdditionalTable;
    std::vector<std::string> mAdditionalTable;

    static std::unordered_map<std::string, std::string> mActualNames;

    RequestParser() noexcept = default;

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

} // namespace get

//--------------------------------------------------------------------------------

#endif // !REQUEST_PARSER_HPP
