#include "get_handler.hpp"

void
get::GetHandler::transmitter(const data::TableInfoAray& request,
                             data::DBSettings& aDBS)
{
    // data::DataRequest req(aRequest, aCondition);
    // auto temp = request.popTableName();
    // if (temp)
    // {
    // }
}

void
get::GetHandler::transmitter(const std::string& aTableName, void* aTable)
{
}

/*

select  * from
journal.journal_table
inner join journal.user on journal.journal_table.teacher_id = journal.user.id
inner join journal.school on journal.user.school_id = journal.school.id;


journal.journal_table
inner join journal.user on journal.journal_table.teacher_id = journal.user.id
inner join journal.user on journal.journal_table.methodist_id = journal.user.id
inner join journal.school on journal.user.school_id = journal.school.id



*/
