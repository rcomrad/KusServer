#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

//--------------------------------------------------------------------------------

namespace get
{

struct Request
{
    std::string statement;

    std::vector<size_t> previous;

    std::vector<std::string> tableNames;
    std::vector<std::string> nicknames;

    std::vector<std::unordered_set<size_t>> columnNums;
};

class RequestHandler
{
public:
    static RequestHandler& getInstance() noexcept;

    Request processRequest(const std::string& aRequest,
                           const std::string& aCondition) noexcept;

private:
    void parseRequest(Request& result, const std::string& aRequest) noexcept;
    void makeTableNames(Request& result) noexcept;
    void makeColumnNums(Request& result) noexcept;

    std::string makeTablePart() const noexcept;
    std::string makeColumnPart() const noexcept;

    std::string getStatement() const noexcept;

    //--------------------------------------------------------------------------------

    static std::unordered_map<std::string, std::string> mTableNames;

    // TODO: remove from memory?
    static std::unordered_map<std::string, std::unordered_map<std::string, int>>
        mTableColumns;
    static std::unordered_map<std::string, std::unordered_map<std::string, int>>
    getTableColumns() noexcept;

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

#endif // !REQUEST_HANDLER_HPP
