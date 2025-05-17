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
            str::String name;
            str::String nickname;
            std::unordered_set<int> columnNums;
            std::vector<str::String> columnNames;
            // std::unique_ptr<DataRequest*> additionalTable;
            str::String additionalTable;
        };

    public:
        size_t size;
        str::String rowStatement;
        std::vector<TableData> tables;

        const TableData& operator[](int num) const noexcept;
        str::String getFullStatement(const char* aCondition) const noexcept;
    };

    static DataRequest process(const char* aRequest) noexcept;

private:
    std::vector<int> mPrev;
    std::vector<str::String> mTables;
    std::vector<str::String> mNicknames;
    std::vector<std::unordered_set<int>> mColumnNums;
    std::vector<std::vector<str::String>> mColumnNames;
    std::vector<bool> mHasAttachment;
    // std::vector<std::unique_ptr<DataRequest>> mAdditionalTable;
    std::vector<str::String> mAdditionalTable;

    static std::unordered_map<str::String, str::String> mActualNames;

    RequestParser() noexcept = default;

    str::String getTables() const noexcept;
    str::String getColumns() const noexcept;

    void parse(const char* aRequest) noexcept;
    void arrangeActualNames() noexcept;
    void arrangeColumns() noexcept;

    void pushTable(int iter,
                   int& last,
                   const char* aRequest,
                   int aOffset) noexcept;

    void pushName(int iter,
                  int& last,
                  const char* aRequest,
                  int curPrev) noexcept;
};

} // namespace get

//--------------------------------------------------------------------------------

#endif // !REQUEST_PARSER_HPP
