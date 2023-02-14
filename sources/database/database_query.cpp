#define DUMMY_NAME "r456rq452rrrr"s
#define DUMMY_NUM  int(2e9)

#include "database_query.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <set>
#include <vector>

#include "domain/error_message.hpp"

#include "sql_wrapper.hpp"

data::DatabaseQuery::DatabaseQuery(const DBSettings& aDBS) noexcept
    : mDatabase(aDBS)
{
    WRITE_LOG("Creating_database_quare");
}

//--------------------------------------------------------------------------------

void
data::DatabaseQuery::createTable(
    const std::string& aTableName,
    const std::vector<ColumnSetting>& aColums) noexcept
{
    mDatabase.createTable(aTableName, aColums);
}

void
data::DatabaseQuery::createEnvironment(const DBSettings& aDBS) noexcept
{
    mDatabase.createEnvironment(aDBS);
}

void
data::DatabaseQuery::dropDatabase(const DBSettings& aDBS) noexcept
{
    mDatabase.deleteDatabase(aDBS.name);
}

//--------------------------------------------------------------------------------

std::vector<data::Type>
data::DatabaseQuery::getColumnTypes(const std::string& aTableName) noexcept
{
    return mDatabase.getColumnTypes(aTableName);
}

std::unordered_map<std::string, uint8_t>
data::DatabaseQuery::getColumnNames(const std::string& aTableName) noexcept
{
    return mDatabase.getColumnNames(aTableName);
}

//--------------------------------------------------------------------------------

// std::vector<data::User>
// data::DatabaseQuery::getUser(const std::string& aLogin) noexcept
// {
//     std::vector<User> res;
//     mDatabase.select("user", "*",
//                      aLogin.empty() ? "" : "login = \'" + aLogin + '\'');
//     std::vector<int> roles;
//     while (true)
//     {
//         mDatabase.step();
//         if (!mDatabase.hasData()) break;
//         res.emplace_back(User());

//         if (mDatabase.hasData())
//         {
//             res.back().id       = mDatabase.getIntFromRow(0).value();
//             res.back().login    = mDatabase.getTextFromRow(1).value();
//             res.back().password = mDatabase.getTextFromRow(2).value();
//             res.back().name     = mDatabase.getTextFromRow(3).value();
//             res.back().surname  = mDatabase.getTextFromRow(4).value();
//             res.back().school   = mDatabase.getIntFromRow(6).value();
//             roles.emplace_back(mDatabase.getIntFromRow(5).value());
//         }
//     }
//     mDatabase.closeStatment();

//     for (auto& i : roles)
//         i <<= 1;

//     mDatabase.select("role", "name");
//     while (true)
//     {
//         mDatabase.step();
//         for (auto& i : roles)
//             i >>= 1;
//         if (!mDatabase.hasData()) break;

//         for (int i = 0; i < roles.size(); ++i)
//         {
//             if (roles[i] & 1)
//             {
//                 res[i].role.emplace_back(mDatabase.getTextFromRow(0).value());
//             }
//         }
//     }
//     mDatabase.closeStatment();

//     return res;
// }

void
data::DatabaseQuery::insert(const std::string& aTableName,
                            const std::vector<std::string>& aData) noexcept
{
    mDatabase.insert(aTableName, aData);
}

// void
// data::DatabaseQuery::setHead(JournalInfo& aJournal) noexcept
// {
//     int grade = aJournal.group_id;
//     if (aJournal.is_group)
//     {
//         mDatabase.select("group", "grade_id",
//                          "id = " + wrap(aJournal.group_id));

//         mDatabase.step();
//         grade = mDatabase.getIntFromRow(0).value();
//         mDatabase.closeStatment();
//     }
//     mDatabase.select("grade", "head_id", "id = " + wrap(grade));
//     mDatabase.step();
//     aJournal.head = mDatabase.getIntFromRow(0).value();
//     mDatabase.closeStatment();
// }

// std::vector<data::Journal>
// data::DatabaseQuery::getJournalByTeacher(int aTeacherID,
//                                          bool aHeadFlag) noexcept
// {
//     std::string cond = aHeadFlag ? "head_id = " : "teacher_id = ";
//     std::vector<Journal> res;
//     mDatabase.select("journal_table", "*",
//                      aTeacherID == 0 ? "" : cond +
//                      std::to_string(aTeacherID));

//     std::vector<int> subjects;
//     while (true)
//     {
//         mDatabase.step();
//         if (!mDatabase.hasData()) break;

//         Journal journal;
//         journal.id         = mDatabase.getIntFromRow(0).value();
//         journal.teacher_id = mDatabase.getIntFromRow(1).value();
//         journal.methodist  = mDatabase.getIntFromRow(2).value();
//         journal.is_group   = mDatabase.getBool(3).value();
//         journal.group_id   = mDatabase.getIntFromRow(4).value();
//         subjects.emplace_back(mDatabase.getIntFromRow(5).value());
//         journal.schedule = mDatabase.getTextFromRow(8).value();
//         res.emplace_back(journal);
//     }
//     mDatabase.closeStatment();

//     for (size_t i = 0; i < subjects.size(); ++i)
//     {
//         mDatabase.select("subject", "name",
//                          "id = " + std::to_string(subjects[i]));
//         mDatabase.step();
//         res[i].subject = mDatabase.getTextFromRow(0).value();
//         mDatabase.closeStatment();
//     }

//     for (auto& jrn : res)
//     {
//         mDatabase.select("lesson", "*",
//                          "journal_table_id = " + std::to_string(jrn.id));
//         while (true)
//         {
//             mDatabase.step();
//             if (!mDatabase.hasData()) break;
//             // std::cout << "===>sus\n";

//             jrn.lessons.emplace_back(Lesson());
//             auto& i = jrn.lessons.back();
//             i.id    = mDatabase.getIntFromRow(0).value();

//             i.themeId     = mDatabase.getIntFromRow(1).value();
//             i.date        = mDatabase.getTextFromRow(2).value();
//             auto homework = mDatabase.getTextFromRow(4);
//             if (homework.has_value()) i.homework = homework.value();
//             auto control = mDatabase.getTextFromRow(5);
//             if (control.has_value()) i.control = control.value();
//         }

//         mDatabase.closeStatment();

//         for (auto& i : jrn.lessons)
//         {
//             mDatabase.select("theme", "name",
//                              "id = " + std::to_string(i.themeId));
//             mDatabase.step();
//             auto theme = mDatabase.getTextFromRow(0);
//             mDatabase.closeStatment();

//             if (theme.has_value()) i.theme = theme.value();

//             mDatabase.select("mark", "id, mark_value, student_id",
//                              "lesson_id = " + std::to_string(i.id));
//             Mark mark;
//             mark.lesson = i.id;
//             while (true)
//             {
//                 mDatabase.step();
//                 if (!mDatabase.hasData()) break;

//                 mark.id      = mDatabase.getIntFromRow(0).value();
//                 mark.value   = mDatabase.getTextFromRow(1).value();
//                 mark.student = mDatabase.getIntFromRow(2).value();
//                 jrn.marks.emplace_back(mark);
//             }
//             mDatabase.closeStatment();
//         }
//     }

//     return res;
// }

// std::vector<data::JournalInfo>
// data::DatabaseQuery::getJournalSimple(int id) noexcept
// {
//     std::vector<JournalInfo> res;
//     mDatabase.select("journal_table", "*",
//                      id == 0 ? "" : "methodist_id = " + wrap(id));

//     std::vector<int> subjects;
//     while (true)
//     {
//         mDatabase.step();
//         if (!mDatabase.hasData()) break;
//         // std::cout << "YEY!\n";

//         JournalInfo journal;
//         journal.id         = mDatabase.getIntFromRow(0).value();
//         journal.teacher_id = mDatabase.getIntFromRow(1).value();
//         journal.methodist  = mDatabase.getIntFromRow(2).value();
//         journal.is_group   = mDatabase.getBool(3).value();
//         journal.group_id   = mDatabase.getIntFromRow(4).value();
//         subjects.emplace_back(mDatabase.getIntFromRow(5).value());
//         journal.planID = mDatabase.getIntFromRow(6).value();
//         // std::cout << "strval: " << mDatabase.getTextFromRow(8).value() <<
//         // "\n";
//         journal.strSchedule = mDatabase.getTextFromRow(8).value();
//         res.emplace_back(journal);
//     }
//     mDatabase.closeStatment();

//     // TODO get all subjects & search throw journals
//     for (size_t i = 0; i < subjects.size(); ++i)
//     {
//         mDatabase.select("subject", "name",
//                          "id = " + std::to_string(subjects[i]));
//         mDatabase.step();
//         res[i].subject = mDatabase.getTextFromRow(0).value();
//         mDatabase.closeStatment();
//     }

//     // TODO get all subjects & search throw journals?
//     for (auto& i : res)
//     {
//         mDatabase.select("plan", "name", "id = " + wrap(i.planID));
//         mDatabase.step();
//         i.planName = mDatabase.getTextFromRow(0).value();
//         mDatabase.closeStatment();
//     }

//     return res;
// }

// std::vector<data::Grade>
// data::DatabaseQuery::getStudents(int aID, const std::string& type) noexcept
// {
//     std::vector<Grade> res;

//     mDatabase.select(type, "*", aID == 0 ? "" : "id = " +
//     std::to_string(aID));

//     while (true)
//     {
//         mDatabase.step();
//         if (!mDatabase.hasData()) break;

//         res.emplace_back(Grade());
//         if (mDatabase.hasData())
//         {
//             res.back().id   = mDatabase.getIntFromRow(0).value();
//             res.back().name = mDatabase.getTextFromRow(1).value();
//             res.back().head = mDatabase.getIntFromRow(2).value();
//         }
//     }
//     mDatabase.closeStatment();

//     for (auto& i : res)
//     {
//         mDatabase.select(type + "_student", "student_id",
//                          type + "_id = " + std::to_string(i.id));

//         while (true)
//         {
//             mDatabase.step();
//             if (!mDatabase.hasData()) break;

//             Student s;
//             s.id = mDatabase.getIntFromRow(0).value();
//             i.students.emplace_back(std::move(s));
//         }
//         mDatabase.closeStatment();

//         for (auto& i : i.students)
//         {
//             mDatabase.select("user", "name, surname",
//                              "id = " + std::to_string(i.id));
//             mDatabase.step();
//             if (!mDatabase.hasData()) continue;

//             i.name    = mDatabase.getTextFromRow(0).value();
//             i.surname = mDatabase.getTextFromRow(1).value();

//             mDatabase.closeStatment();
//         }
//     }

//     return res;
// }

// std::vector<data::Grade>
// data::DatabaseQuery::getGrade(int aID) noexcept
// {
//     return getStudents(aID, "grade");
// }

// std::vector<data::Grade>
// data::DatabaseQuery::getGroup(int aID) noexcept
// {
//     return getStudents(aID, "group");
// }

// void
// data::DatabaseQuery::turnHead(int aID, bool flag) noexcept
// {
//     std::cout << aID << "\n";
//     mDatabase.select("role", "id", "name = " + wrap("grade_head"));
//     mDatabase.step();
//     auto num = 1 << (mDatabase.getIntFromRow(0).value() - 1);
//     mDatabase.closeStatment();
//     std::cout << num << "\n";

//     mDatabase.select("user", "role_id", "id = " + wrap(aID));
//     mDatabase.step();
//     auto rol = mDatabase.getIntFromRow(0).value();
//     mDatabase.closeStatment();
//     std::cout << rol << "\n";

//     if (flag) rol += num;
//     else rol -= num;
//     std::cout << rol << "\n";

//     mDatabase.update("user", "role_id = " + wrap(rol), "id = " + wrap(aID));
// }

// int
// data::DatabaseQuery::manageGrade(Grade aGrade, std::string aType) noexcept
// {
//     if (aGrade.id == 0)
//     {
//         // std::cout << aGrade.grade_id << "\n";
//         mDatabase.insert(aType, {wrap(DUMMY_NAME), wrap(aGrade.head)});

//         mDatabase.select(aType, "id", "name = " + wrap(DUMMY_NAME));
//         mDatabase.step();
//         aGrade.id = mDatabase.getIntFromRow(0).value();
//         mDatabase.closeStatment();

//         mDatabase.update(aType, "name = " + wrap(aGrade.name),
//                          "id = " + wrap(aGrade.id));
//         if (aType == "grade")
//         {
//             turnHead(aGrade.head, true);
//         }
//     }
//     else
//     {
//         std::string str;
//         str += "name = " + wrap(aGrade.name, ',');
//         str +=
//             (aType == "grade" ? "head_id" : "grade_id") + " = "s +
//             wrap(aGrade.head);

//         if (aType == "grade")
//         {
//             mDatabase.select("grade", "head_id", "id = " + wrap(aGrade.id));
//             mDatabase.step();
//             int oldHeadID = mDatabase.getIntFromRow(0).value();
//             mDatabase.closeStatment();

//             turnHead(oldHeadID, false);
//             turnHead(aGrade.head, true);
//         }

//         mDatabase.update(aType, str, "id = " + wrap(aGrade.id));
//         mDatabase.deleteRow(aType + "_student",
//                             aType + "_id = " + wrap(aGrade.id));
//     }

//     for (auto& i : aGrade.students)
//     {
//         mDatabase.insert(aType + "_student", {wrap(aGrade.id), wrap(i.id)});
//     }

//     return aGrade.id;
// }

// void
// data::DatabaseQuery::dropGrade(const std::vector<int>& aIDs,
//                                std::string aType) noexcept
// {
//     for (auto& i : aIDs)
//     {
//         mDatabase.deleteRow(aType, "id = " + wrap(i));
//         mDatabase.deleteRow(aType + "_student", "grade_id = " + wrap(i));
//     }
// }

// void
// data::DatabaseQuery::dropUsers(const std::vector<int>& aIDs) noexcept
// {
//     for (auto& i : aIDs)
//     {
//         mDatabase.select("user", "role_id", "id = " + wrap(i));
//         mDatabase.step();
//         auto role = mDatabase.getIntFromRow(0);
//         mDatabase.closeStatment();

//         mDatabase.deleteRow("user", "id = " + wrap(i));

//         if (role == 1)
//         {
//             mDatabase.deleteRow("grade_student", "student_id = " + wrap(i));
//             mDatabase.deleteRow("group_student", "student_id = " + wrap(i));
//             mDatabase.deleteRow("mark", "student_id = " + wrap(i));
//         }
//     }
// }

// void
// data::DatabaseQuery::dropJournal(const std::vector<int>& aIDs) noexcept
// {
//     for (auto& i : aIDs)
//     {
//         mDatabase.deleteRow("journal_table", "id = " + wrap(i));
//     }
// }

// std::vector<data::Plan>
// data::DatabaseQuery::getPlan(int aID) noexcept
// {
//     auto sub = getSubjects();

//     std::vector<data::Plan> result;
//     mDatabase.select("plan", "*");
//     while (true)
//     {
//         mDatabase.step();
//         // std::cout << "--> 1\n";
//         if (!mDatabase.hasData()) break;
//         // std::cout << "--> 2\n";
//         result.push_back(Plan());
//         result.back().id      = mDatabase.getIntFromRow(0).value();
//         result.back().subject = sub[mDatabase.getIntFromRow(1).value() - 1];
//         result.back().name    = mDatabase.getTextFromRow(2).value();
//         result.back().url     = mDatabase.getTextFromRow(3).value();
//     }
//     mDatabase.closeStatment();

//     return result;
// }
// #include <sstream>
// int
// data::DatabaseQuery::managePlan(Plan aPlan) noexcept
// {
//     if (aPlan.id != 0)
//     {
//         // mDatabase.select("plan", "url", "id = " + SQLWrapperS(aPlan.id));
//         mDatabase.deleteRow("plan", "id = " + wrap(aPlan.id));
//         // mDatabase.deleteRow("plan_theme", "plan_id = " +
//         // SQLWrapperS(aPlan.id));
//     }

//     mDatabase.insert(
//         "plan", {wrap(aPlan.subjectID), wrap(DUMMY_NAME), wrap(aPlan.url)});

//     mDatabase.select("plan", "id", "name = " + wrap(DUMMY_NAME));
//     mDatabase.step();
//     aPlan.id = mDatabase.getIntFromRow(0).value();
//     mDatabase.closeStatment();
//     mDatabase.update("plan", "name = " + wrap(aPlan.name),
//                      "id = " + wrap(aPlan.id));

//     std::vector<int> planThemeIDs;
//     mDatabase.select("theme", "id", "plan_id = " + wrap(aPlan.id));
//     while (true)
//     {
//         mDatabase.step();
//         if (!mDatabase.hasData()) break;
//         planThemeIDs.emplace_back(mDatabase.getIntFromRow(0).value());
//     }
//     mDatabase.closeStatment();
//     reverse(planThemeIDs.begin(), planThemeIDs.end());
//     // std::cout << "theme count:" << planThemeIDs.size() << "\n";

//     mDatabase.deleteRow("theme", "plan_id = " + wrap(aPlan.id));

//     // std::cout << "YEAH!1\n";
//     std::ifstream themes(aPlan.url);
//     // std::cout << "YEAH!2\n";
//     std::string s;
//     while (std::getline(themes, s))
//     {
//         // std::cout << "YEAH!3\n";
//         std::stringstream ss;
//         ss << s;

//         std::string theme;
//         std::string count;
//         std::getline(ss, theme, ';');
//         std::getline(ss, count, ';');
//         // std::cout << "YEAH!4\n";
//         // std::cout << theme << "\n";
//         // std::cout << count << "\n";
//         for (int i = 0; i < std::stoi(count); ++i)
//         {
//             // std::cout << "YEAH!5\n";
//             mDatabase.insert("theme", {wrap(aPlan.id), wrap(theme)},
//                              planThemeIDs.size() ? planThemeIDs.back() : 0);
//             if (planThemeIDs.size()) planThemeIDs.pop_back();
//         }
//     }

//     return 0;
// }

// int
// data::DatabaseQuery::getNextFileNumber() noexcept
// {

//     mDatabase.select("file", "num");
//     mDatabase.step();
//     int res = mDatabase.getIntFromRow(0).value();
//     mDatabase.closeStatment();
//     mDatabase.update("file", "num = " + wrap(res + 1), "id = 1");

//     return res;
// }

// void
// data::DatabaseQuery::updateLesson(int aID, const std::string& aHomework,
//                                   const std::string& aControl) noexcept
// {
//     // std::cout << aID << " " << aHomework << " " << aControl << "\n";

//     mDatabase.update("lesson",
//                      "homework = \'" + aHomework + "\', control = " + "\'" +
//                          aControl + "\'",
//                      "id = " + std::to_string(aID));
// }

// int
// data::DatabaseQuery::updateMark(int aID, int aLessonID, int aStudentID,
//                                 const std::string& aValue) noexcept
// {
//     if (aID == -1)
//     {
//         mDatabase.insert("mark",
//                          {"\'" + aValue + '\'', "" +
//                          std::to_string(aStudentID),
//                           "" + std::to_string(aLessonID)});
//         mDatabase.select("mark", "id",
//                          "mark_value = \'" + aValue +
//                              "\' AND student_id = " +
//                              std::to_string(aStudentID) + " AND lesson_id = "
//                              + std::to_string(aLessonID));

//         mDatabase.step();
//         aID = mDatabase.getIntFromRow(0).value();
//         mDatabase.closeStatment();
//     }
//     else
//     {
//         mDatabase.update("mark", "mark_value = \'" + aValue + "\'",
//                          "id = " + std::to_string(aID));
//     }

//     return aID;
// }

// std::vector<std::string>
// data::DatabaseQuery::getSubjects() noexcept
// {
//     std::vector<std::string> res;
//     mDatabase.select("subject", "name");
//     while (true)
//     {
//         mDatabase.step();
//         if (!mDatabase.hasData()) break;
//         res.emplace_back(mDatabase.getTextFromRow(0).value());
//     }
//     mDatabase.closeStatment();
//     return res;
// }

// data::RowArray
// data::DatabaseQuery::getSubjects2() noexcept
// {
//     return mDatabase.selectAll("subject");
// }

// data::Table<data::Subject>
// data::DatabaseQuery::getSubjects3() noexcept
// {
//     return mDatabase.selectAll<data::Subject>("subject");
// }

// int
// data::DatabaseQuery::manageUser(User&& aUser) noexcept
// {
//     std::set<std::string> roleSet(aUser.role.begin(), aUser.role.end());
//     // std::cout << "BUH!"
//     //    << "\n";
//     int roleVal = 0;
//     int cnt     = -1;
//     mDatabase.select("role", "name");
//     while (true)
//     {
//         mDatabase.step();
//         cnt++;
//         if (!mDatabase.hasData()) break;
//         if (roleSet.count(mDatabase.getTextFromRow(0).value()) == 0)
//         continue; roleVal += 1 << cnt;
//     }
//     mDatabase.closeStatment();
//     // std::cout << "role: " << roleVal << "\n";
//     if (roleVal == 0) roleVal = 1;

//     if (aUser.id == 0)
//     {
//         mDatabase.insert(
//             "user", {"\'" DUMMY_NAME "\'", "\'" + aUser.password + "\'",
//                      "\'" + aUser.name + "\'", "\'" + aUser.surname + "\'",
//                      std::to_string(roleVal), std::to_string(aUser.school)});

//         mDatabase.select("user", "id", "login = \'" DUMMY_NAME "\'");
//         mDatabase.step();
//         aUser.id = mDatabase.getIntFromRow(0).value();
//         mDatabase.closeStatment();

//         mDatabase.update("user", "login = \'" + aUser.login + "\'",
//                          "id = " + std::to_string(aUser.id));
//     }
//     else
//     {
//         mDatabase.select("user", "*", "id = " + std::to_string(aUser.id));
//         mDatabase.step();

//         if (aUser.login.empty())
//             aUser.login = mDatabase.getTextFromRow(1).value();
//         if (aUser.password.empty())
//             aUser.password = mDatabase.getTextFromRow(2).value();
//         if (aUser.name.empty())
//             aUser.name = mDatabase.getTextFromRow(3).value();
//         if (aUser.surname.empty())
//             aUser.surname = mDatabase.getTextFromRow(4).value();
//         if (aUser.role.empty()) roleVal = mDatabase.getIntFromRow(5).value();
//         if (aUser.school == 0)
//             aUser.school = mDatabase.getIntFromRow(6).value();

//         mDatabase.closeStatment();

//         std::string login    = "login = \'" + aUser.login + "\', ";
//         std::string password = "password = \'" + aUser.password + "\', ";
//         std::string name     = "name = \'" + aUser.name + "\', ";
//         std::string surname  = "surname = \'" + aUser.surname + "\', ";
//         std::string role     = "role_id = " + std::to_string(roleVal) + ", ";
//         std::string school   = "school_id = " + std::to_string(aUser.school)
//         + " ";

//         mDatabase.update("user",
//                          login + password + name + surname + role + school,
//                          "id = " + std::to_string(aUser.id));
//     }
//     return aUser.id;
// }
// #include <algorithm>
// int
// data::DatabaseQuery::manageJournal(JournalInfo&& aJournal) noexcept
// {
//     // std::cout << aJournal.subject.size() << "\n";
//     // std::cout << "SUS1\n";
//     mDatabase.select("subject", "id", "name = \'" + aJournal.subject + "\'");
//     // std::cout << "SUS2\n";
//     mDatabase.step();
//     // std::cout << "SUS3\n";
//     int subject = mDatabase.getIntFromRow(0).value();
//     // std::cout << "SUS4\n";
//     mDatabase.closeStatment();
//     // std::cout << "SUS5\n";

//     std::string schedule;
//     for (auto& i : aJournal.schedule)
//     {
//         schedule.push_back(i + '0');
//     }
//     // std::cout << "---" << schedule << "\n";

//     if (aJournal.id == 0)
//     {
//         mDatabase.insert("journal_table",
//                          {SQLWrapper(DUMMY_NUM),
//                          SQLWrapper(aJournal.methodist),
//                           SQLWrapper(aJournal.is_group),
//                           SQLWrapper(aJournal.group_id), SQLWrapper(subject),
//                           SQLWrapper(aJournal.planID),
//                           SQLWrapper(aJournal.head), SQLWrapper(schedule)});

//         mDatabase.select("journal_table", "id",
//                          "teacher_id = " + wrap(DUMMY_NUM));
//         mDatabase.step();
//         aJournal.id = mDatabase.getIntFromRow(0).value();
//         mDatabase.closeStatment();

//         mDatabase.update("journal_table",
//                          "teacher_id = " + wrap(aJournal.teacher_id),
//                          "id = " + wrap(aJournal.id));

//         std::vector<int> themes;
//         mDatabase.select("theme", "id", "plan_id = " +
//         wrap(aJournal.planID)); while (true)
//         {
//             mDatabase.step();
//             if (!mDatabase.hasData()) break;
//             themes.emplace_back(mDatabase.getIntFromRow(0).value());
//         }
//         mDatabase.closeStatment();

//         mDatabase.select("school", "start_date",
//                          "id = " + wrap(aJournal.schoolId));
//         mDatabase.step();
//         auto dateStr = mDatabase.getTextFromRow(0).value();
//         mDatabase.closeStatment();
//         // std::cout << "SUS1!\n";
//         // std::cout << (int)uint16_t(std::stoi(dateStr.substr(0, 4))) <<
//         "\n";
//         // std::cout << (int)uint8_t(std::stoi(dateStr.substr(5, 2))) <<
//         "\n";
//         // std::cout << (int)uint8_t(std::stoi(dateStr.substr(8, 2))) <<
//         "\n"; boost::gregorian::date
//         date{uint16_t(std::stoi(dateStr.substr(0, 4))),
//                                     uint8_t(std::stoi(dateStr.substr(5, 2))),
//                                     uint8_t(std::stoi(dateStr.substr(8,
//                                     2)))};
//         // std::cout << "SUS2!\n";
//         // std::cout << int(date.day_of_week()) << "\n";
//         // std::cout << aJournal.schedule.size() << "\n";

//         // for (auto& i : aJournal.schedule)
//         // std::cout << i << " ";
//         // std::cout << "\n";
//         auto it = std::lower_bound(aJournal.schedule.begin(),
//                                    aJournal.schedule.end(),
//                                    date.day_of_week());
//         if (it == aJournal.schedule.end())
//         {
//             it = aJournal.schedule.begin();
//             do
//             {
//                 date += boost::gregorian::days(1);
//             } while (date.day_of_week() != 1);
//         }
//         int ind = it - aJournal.schedule.begin();

//         std::string ssss = std::to_string(date.year()) + "-" +
//                            std::to_string(date.month()) + "-" +
//                            std::to_string(date.day());
//         // std::cout << ssss << "\n";

//         // std::cout << ind << "\n";
//         for (int k = 0; k < themes.size();)
//         {
//             auto& i = themes[k];
//             // std::cout << "SUS3!\n";
//             // std::cout << "array: " << aJournal.schedule[ind] << "\n";
//             // std::cout << "array - 1: " << aJournal.schedule[ind] - 1 <<
//             "\n"; auto newData =
//                 date + boost::gregorian::days(aJournal.schedule[ind] - 1);
//             ++ind;
//             if (ind == aJournal.schedule.size())
//             {
//                 ind = 0;
//                 date += boost::gregorian::days(7);
//             }

//             std::string sss = std::to_string(newData.year()) + "-" +
//                               std::to_string(newData.month()) + "-" +
//                               std::to_string(newData.day());

//             mDatabase.select("holiday", "*", "date_val = " + wrap(sss));
//             mDatabase.step();
//             auto temp = mDatabase.getIntFromRow(0);
//             mDatabase.closeStatment();
//             if (temp.has_value()) continue;
//             ++k;

//             mDatabase.insert("lesson", {wrap(i), wrap(sss),
//             wrap(aJournal.id)});
//         }
//         // std::cout << "SUS14\n";
//     }
//     else
//     {
//         mDatabase.select("journal_table", "*", "id = " + wrap(aJournal.id));
//         mDatabase.step();

//         if (aJournal.teacher_id == 0)
//             aJournal.teacher_id = mDatabase.getIntFromRow(1).value();
//         if (aJournal.methodist == 0)
//             aJournal.methodist = mDatabase.getIntFromRow(2).value();
//         if (aJournal.group_id == 0)
//         {
//             aJournal.is_group = mDatabase.getBool(3).value();
//             aJournal.group_id = mDatabase.getIntFromRow(4).value();
//         }
//         if (subject == 0) subject = mDatabase.getIntFromRow(5).value();
//         mDatabase.closeStatment();

//         std::string str;
//         str += "teacher_id = " + wrap(aJournal.teacher_id);
//         str += "methodist_id = " + wrap(aJournal.methodist);
//         str += "is_group = " + wrap(aJournal.is_group);
//         str += "group_id = " + wrap(aJournal.group_id);
//         str += "subject_id = " + wrap(aJournal.subject);
//         str += "schedule = " + wrap(schedule);

//         mDatabase.update("user", str, "id = " + wrap(aJournal.id));
//     }
//     return aJournal.id;
// }
