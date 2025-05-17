#include "journal_handler.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <fstream>
#include <set>
#include <string>

#include "domain/date_time.hpp"

#include "database/connection_manager.hpp"
#include "database/safe_sql_wrapper.hpp"

#include "text_data/file.hpp"

crow::json::wvalue
post::JournalHandler::process(
    post::PostRequest<data::JournalTable>& aReq) noexcept
{
    auto& journal = aReq.data;

    std::string temp = journal.id ? journal.schedule : "";
    {
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.write(journal);
        if (!temp.empty())
        {
            journal = connection.val.getData<data::JournalTable>(
                "id=" + data::safeWrap(journal.id));
        }
    }

    if (temp.empty() || journal.schedule != temp) makeSchedule(journal);
    return {journal.id};
}

crow::json::wvalue
post::JournalHandler::rawDataHandler(data::RawData& aData) noexcept
{
    if (aData.additionalInfo.size())
    {
        for (size_t i = 0; i < aData.value.size(); ++i)
        {
            if (aData.additionalInfo[i].size())
            {
                aData.value[i].emplace_back();
                for (auto& j : aData.additionalInfo[i])
                {
                    aData.value[i].back() += j;
                    aData.value[i].back().push_back(' ');
                }
            }
        }
    }

    data::DataArray<data::JournalTable> journals(aData.value);
    {
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.insert(journals);
    }

    for (auto& i : journals)
    {
        makeSchedule(i);
    }
    return {"200"};
}

void
post::JournalHandler::makeSchedule(data::JournalTable& aJournal) noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();

    std::vector<int> schedule;
    for (auto i : aJournal.schedule)
        if (i >= '1' && i <= '7') schedule.emplace_back(i - '1');

    data::User methodist = connection.val.getData<data::User>(
        "id = " + data::safeWrap(aJournal.methodistID));

    int methodistSchool = -1;
    if (methodist.id) methodistSchool = methodist.schoolID;
    data::School school = connection.val.getData<data::School>(
        "id = " + data::safeWrap(methodistSchool));

    int schoolID  = -1;
    uint16_t year = 1991;
    uint8_t month = 12;
    uint8_t day   = 26;
    // if (school.id)
    // {
    //     schoolID = school.id;

    //     year  = uint16_t(std::stoi(school.startDate.substr(0, 4)));
    //     month = uint8_t(std::stoi(school.startDate.substr(5, 2)));
    //     day   = uint8_t(std::stoi(school.startDate.substr(8, 2)));
    // };

    // data::DataArray<data::Holiday> holidays =
    //     connection.val.getDataArray<data::Holiday>("school_id = " +
    //                                                data::safeWrap(schoolID));

    // boost::gregorian::date startDate{year, month, day};
    // boost::gregorian::date date = startDate;
    // while (date.day_of_week() != 1)
    // {
    //     date -= boost::gregorian::days(1);
    // }

    // int j = 0;
    // while (j < schedule.size() &&
    //        date + boost::gregorian::days(schedule[j]) < startDate)
    // {
    //     j++;
    // }

    // // std::set<std::string> holidaysSet;
    // // for (auto& i : holidays)
    // // {
    // //     holidaysSet.insert(i.dateVal);
    // // }
    // std::set<boost::gregorian::date> holidaysSet;
    // for (auto& i : holidays)
    // {
    //     holidaysSet.insert(dom::DateTime::getDate(i.dateVal));
    // }

    // data::DataArray<data::Theme> themes =
    //     connection.val.getDataArray<data::Theme>(
    //         "plan_id = " + data::safeWrap(aJournal.planID));
    // data::DataArray<data::Lesson> lessons;
    // for (int i = 0; i < themes.size();)
    // {
    //     if (j == schedule.size())
    //     {
    //         j = 0;
    //         date += boost::gregorian::days(7);
    //     }

    //     auto newData = date + boost::gregorian::days(schedule[j++]);
    //     if (holidaysSet.count(newData)) continue;
    //     auto dateStr = dom::DateTime::getDateOnly(newData);

    //     lessons.emplace_back();
    //     lessons.back().themeID        = themes[i].id;
    //     lessons.back().dateVal        = dateStr;
    //     lessons.back().journalTableID = aJournal.id;

    //     ++i;
    // }

    // connection.val.write(lessons);
}

void
post::JournalHandler::remakeSchedule(data::JournalTable& aJournal,
                                     const std::string& fromID,
                                     const std::string& toVal) noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();

    std::vector<int> schedule;
    for (auto i : aJournal.schedule)
        if (i >= '1' && i <= '7') schedule.emplace_back(i - '1');

    data::User methodist = connection.val.getData<data::User>(
        "id = " + data::safeWrap(aJournal.methodistID));

    int methodistSchool = -1;
    if (methodist.id) methodistSchool = methodist.schoolID;
    data::School school = connection.val.getData<data::School>(
        "id = " + data::safeWrap(methodistSchool));

    int schoolID  = -1;
    uint16_t year = 1991;
    uint8_t month = 12;
    uint8_t day   = 26;
    if (school.id)
    {
        schoolID = school.id;

        year  = uint16_t(std::stoi(school.startDate.substr(0, 4)));
        month = uint8_t(std::stoi(school.startDate.substr(5, 2)));
        day   = uint8_t(std::stoi(school.startDate.substr(8, 2)));
    };

    data::DataArray<data::Holiday> holidays =
        connection.val.getDataArray<data::Holiday>("school_id = " +
                                                   data::safeWrap(schoolID));

    boost::gregorian::date startDate{year, month, day};
    boost::gregorian::date date = startDate;
    while (date.day_of_week() != 1)
    {
        date -= boost::gregorian::days(1);
    }

    int j = 0;
    while (j < schedule.size() &&
           date + boost::gregorian::days(schedule[j]) < startDate)
    {
        j++;
    }

    // std::set<boost::gregorian::date> holidaysSet;
    // for (auto& i : holidays)
    // {
    //     holidaysSet.insert(dom::DateTime::getDate(i.dateVal));
    // }

    // boost::gregorian::date toDate = dom::DateTime::getDate(toVal);
    // data::DataArray<data::Lesson> lessons =
    //     connection.val.getDataArray<data::Lesson>("id>" + fromID);
    // for (auto& i : lessons)
    // {
    //     if (j == schedule.size())
    //     {
    //         j = 0;
    //         date += boost::gregorian::days(7);
    //     }

    //     auto newData = date + boost::gregorian::days(schedule[j++]);
    //     if (newData > toDate)
    //     {
    //         i.dateVal = toVal;
    //     }

    //     if (holidaysSet.count(newData)) continue;
    //     auto dateStr = dom::DateTime::getDateOnly(newData);
    //     i.dateVal    = dateStr;
    // }

    // connection.val.write(lessons);
}
