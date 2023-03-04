#ifndef DATABASE_QUERY_HPP
#define DATABASE_QUERY_HPP

//--------------------------------------------------------------------------------

#include <map>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "domain/string.hpp"

#include "postgresql.hpp"

//--------------------------------------------------------------------------------

namespace data
{
class DatabaseQuery
{
public:
    DatabaseQuery(const DBSettings& aDBS) noexcept;
    ~DatabaseQuery() = default;

    DatabaseQuery(const DatabaseQuery& other)            = delete;
    DatabaseQuery& operator=(const DatabaseQuery& other) = delete;

    DatabaseQuery(DatabaseQuery&& other) noexcept            = default;
    DatabaseQuery& operator=(DatabaseQuery&& other) noexcept = default;

    std::vector<data::User> getUser(const std::string& aLogin = "") noexcept;

    template <typename T>
    Table<T> getData(const std::string& aCondition = "") noexcept
    {
        return mDatabase.selectAll<T>({}, aCondition);
    }

    template <typename T>
    int insert(const Table<T>& aData) noexcept
    {
        return mDatabase.insert<T>(aData);
    }

    template <typename T>
    int update(const Table<T>& aData) noexcept
    {
        return mDatabase.update<T>(aData);
    }

    // TODO: delete
    int insert(const std::string& aTableName,
               const std::vector<std::string>& aData) noexcept;

    void createTable(const std::string& aTableName,
                     const std::vector<ColumnSetting>& aColumns) noexcept;
    void createEnvironment(const DBSettings& aDBS) noexcept;
    void dropDatabase(const DBSettings& aDBS) noexcept;

    std::vector<data::Type> getColumnTypes(
        const std::string& aTableName) noexcept;
    std::unordered_map<std::string, uint8_t> getColumnNames(
        const std::string& aTableName) noexcept;

    // void insert(const std::string& aTableName,
    //             const std::vector<std::string>& aData) noexcept;

    // std::vector<Journal> getJournalByTeacher(int aTeacherID = 0,
    //                                          bool aHeadFlag = false)
    //                                          noexcept;

    // void updateLesson(int aID, const std::string& aHomework,
    //                   const std::string& aControl) noexcept;
    // int updateMark(int aID, int aLessonID, int aStudentID,
    //                const std::string& aValue) noexcept;

    // std::vector<std::string> getSubjects() noexcept;
    // RowArray getSubjects2() noexcept;
    // Table<Subject> getSubjects3() noexcept;

    // int manageUser(User&& aUser) noexcept;
    // int manageJournal(JournalInfo&& aJournal) noexcept;
    // void setHead(JournalInfo& aJournal) noexcept;
    // std::vector<JournalInfo> getJournalSimple(int id) noexcept;

    // int manageGrade(Grade aGrade, std::string aType) noexcept;

    // void dropGrade(const std::vector<int>& aIDs, std::string aType) noexcept;
    // void dropUsers(const std::vector<int>& aIDs) noexcept;
    // void dropJournal(const std::vector<int>& aIDs) noexcept;

    // std::vector<Plan> getPlan(int aID = 0) noexcept;
    // int managePlan(Plan aPlan) noexcept;

    // int getNextFileNumber() noexcept;

    // void turnHead(int aID, bool flag) noexcept;

private:
    Postgresql mDatabase;

    // std::vector<data::Grade> getStudents(int aID,
    //                                      const std::string& type) noexcept;
};
} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATABASE_QUERY_HPP
