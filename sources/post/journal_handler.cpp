#include "journal_handler.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <fstream>
#include <set>
#include <string>

crow::json::wvalue
post::JournalHandler::process(const crow::request& aReq,
                              data::DatabaseQuery& aDBQ)
{
    auto req     = crow::json::load(aReq.body);
    auto journal = parseRequest<data::Journal_table>(req).table;
    aDBQ.update(journal);
    makeSchedule(journal[0], aDBQ);
    return {journal[0].id};
}

crow::json::wvalue
post::JournalHandler::uploadFromFile(const crow::request& aReq,
                                     data::DatabaseQuery& aDBQ)
{
    crow::json::wvalue res;

    crow::multipart::message msg(aReq);
    std::string filePath = uploadFile(msg, aDBQ);

    std::string type = msg.get_part_by_name("index").body;
    if (type == "data")
    {
        res = dataFileUpload(filePath, aDBQ);
    }

    return res;
}

crow::json::wvalue
post::JournalHandler::dataFileUpload(const std::string& aFilePath,
                                     data::DatabaseQuery& aDBQ)
{
    auto data = dataFileParser<data::Journal_table>(aFilePath, 1);
    for (int i = 0; i < data.table.size(); ++i)
    {
        data.table[i].schedule = std::move(data.additionalLines[i][0]);
    }

    aDBQ.insert(data.table);
    for (auto& i : data.table)
    {
        makeSchedule(i, aDBQ);
    }
    return {200};
}

void
post::JournalHandler::makeSchedule(data::Journal_table& aJournal,
                                   data::DatabaseQuery& aDBQ)
{
    std::vector<int> schedule;
    for (auto i : aJournal.schedule)
        if (i >= '1' && i <= '7') schedule.emplace_back(i - '0');

    data::Table<data::User> methodist =
        aDBQ.getData<data::User>("id = " + data::wrap(aJournal.methodist_id));

    data::Table<data::Theme> themes =
        aDBQ.getData<data::Theme>("plan_id = " + data::wrap(aJournal.plan_id));

    int methodistID = 0;
    if (methodist.size()) methodistID = methodist[0].school_id;
    data::Table<data::School> school =
        aDBQ.getData<data::School>("id = " + data::wrap(methodistID));

    int schoolID  = 0;
    uint16_t year = 1991;
    uint8_t month = 12;
    uint8_t day   = 26;
    if (school.size())
    {
        schoolID = school[0].id;

        year  = uint16_t(std::stoi(school[0].start_date.substr(0, 4)));
        month = uint8_t(std::stoi(school[0].start_date.substr(5, 2)));
        day   = uint8_t(std::stoi(school[0].start_date.substr(8, 2)));
    };

    data::Table<data::Holiday> holidays =
        aDBQ.getData<data::Holiday>("school_id = " + data::wrap(schoolID));

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
        if (j == schedule.size())
        {
            j = 0;
            date += boost::gregorian::days(7);
        }

        auto newData = date + boost::gregorian::days(schedule[j++]);
        if (holidaysSet.count(newData)) continue;

        std::string dateStr = std::to_string(newData.year()) + "-" +
                              std::to_string(newData.month()) + "-" +
                              std::to_string(newData.day());

        lessons.emplace_back();
        lessons.back().theme_id         = themes.data[i].id;
        lessons.back().date_val         = dateStr;
        lessons.back().journal_table_id = aJournal.id;

        ++i;
    }

    aDBQ.insert<data::Lesson>(lessons);
}
