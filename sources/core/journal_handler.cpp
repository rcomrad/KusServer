#include "journal_handler.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <fstream>
#include <set>
#include <string>

crow::json::wvalue
core::JournalHandler::process(const crow::request& aReq,
                              data::DatabaseQuery& aDBQ)
{
    auto req     = crow::json::load(aReq.body);
    auto journal = getStructTable<data::Journal_table>(req, aDBQ);
    std::vector<int> schedule;
    for (auto& day : req["schedule"])
    {
        schedule.emplace_back(day.i());
    }
    make(journal, schedule, aDBQ);

    return {};
}

void
core::JournalHandler::loadFromFile(std::string_view aFileName,
                                   data::DatabaseQuery& aDBQ)
{
    std::ifstream inp(aFileName.data());

    std::string s;
    std::getline(inp, s);

    data::Table<data::Journal_table> journal;
    int teacherID;
    while (inp >> teacherID)
    {
        journal.clear();
        journal.emplace_back();

        journal.back().teacher_id = teacherID;
        inp >> journal.back().methodist_id;
        inp >> journal.back().is_group;
        inp >> journal.back().group_id;
        inp >> journal.back().subject_id;
        inp >> journal.back().plan_id;
        inp >> journal.back().head_id;

        std::getline(inp, s, '\n');
        std::getline(inp, s, '\n');
        journal.back().schedule = s;
        std::vector<int> schedule;
        for (auto i : s)
            if (i != ' ') schedule.emplace_back(i - '0');
        make(journal, schedule, aDBQ);
    }
}

void
core::JournalHandler::make(data::Table<data::Journal_table>& aJournal,
                           std::vector<int> aSchedule,
                           data::DatabaseQuery& aDBQ)
{
    // TODO:
    auto temp              = aJournal[0].teacher_id;
    aJournal[0].teacher_id = 999999;
    aDBQ.insert<data::Journal_table>(aJournal);
    aJournal =
        aDBQ.getData<data::Journal_table>("teacher_id = " + data::wrap(999999));

    aJournal[0].teacher_id = temp;
    aDBQ.update<data::Journal_table>(aJournal);

    makeSchedule(aJournal, aSchedule, aDBQ);
}

void
core::JournalHandler::makeSchedule(data::Table<data::Journal_table>& aJournal,
                                   std::vector<int> aSchedule,
                                   data::DatabaseQuery& aDBQ)
{
    data::Table<data::User> methodist = aDBQ.getData<data::User>(
        "id = " + data::wrap(aJournal[0].methodist_id));

    data::Table<data::Theme> themes = aDBQ.getData<data::Theme>(
        "plan_id = " + data::wrap(aJournal[0].plan_id));

    data::Table<data::School> school = aDBQ.getData<data::School>(
        "id = " + data::wrap(methodist[0].school_id));

    data::Table<data::Holiday> holidays =
        aDBQ.getData<data::Holiday>("school_id = " + data::wrap(school[0].id));

    boost::gregorian::date startDate{
        uint16_t(std::stoi(school[0].start_date.substr(0, 4))),
        uint8_t(std::stoi(school[0].start_date.substr(5, 2))),
        uint8_t(std::stoi(school[0].start_date.substr(8, 2)))};
    boost::gregorian::date date = startDate;
    while (date.day_of_week() != 1)
    {
        date -= boost::gregorian::days(1);
    }

    int j = 0;
    while (j < aSchedule.size() &&
           date + boost::gregorian::days(aSchedule[j]) < startDate)
    {
        j++;
    }

    std::set<boost::gregorian::date> holidaysSet;
    for (auto& i : holidays)
    {
        holidaysSet.insert(boost::gregorian::date{
            uint16_t(std::stoi(i.date_val.substr(0, 4))),
            uint8_t(std::stoi(i.date_val.substr(5, 2))),
            uint8_t(std::stoi(i.date_val.substr(8, 2)))});
    }

    data::Table<data::Lesson> lessons;
    for (int i = 0; i < themes.size();)
    {
        if (j == aSchedule.size())
        {
            j = 0;
            date += boost::gregorian::days(7);
        }

        auto newData = date + boost::gregorian::days(aSchedule[j++]);
        if (holidaysSet.count(newData)) continue;

        std::string dateStr = std::to_string(newData.year()) + "-" +
                              std::to_string(newData.month()) + "-" +
                              std::to_string(newData.day());

        lessons.emplace_back();
        lessons.back().theme_id         = themes.data[i].id;
        lessons.back().date_val         = dateStr;
        lessons.back().journal_table_id = aJournal[0].id;

        ++i;
    }

    aDBQ.insert<data::Lesson>(lessons);
}
