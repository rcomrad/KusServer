#include "question_handler.hpp"

#include "file/file.hpp"
#include "file/path.hpp"

crow::json::wvalue
get::QuestionHandler::process(const std::vector<int>& aColumn,
                              data::SmartConnection& aConnection) noexcept
{
    crow::json::wvalue result;

    auto table = aConnection.val.select2<data::Question>(aColumn);
    table.turnOffColumn("jury_answer");
    
    auto path = file::Path::getInstance().getPath("question");
    if (path)
    {
        auto legend = file::File::getAllData(path.value() + table[0].nickname +
                                             "/legend.txt");

        table.turnOffColumn("nickname");
        auto tableList = getTableAsList(table)[0];

        tableList["legend"] = std::move(legend);

        result["question"] = std::move(tableList);
    }
    return result;
}
