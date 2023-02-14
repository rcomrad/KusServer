#include "post_handler.hpp"

std::string
core::PostHandler::uploadFile(crow::multipart::message& aMsg,
                               data::DatabaseQuery& aDBQ)
{
    auto filename = aMsg.get_part_by_name("filename").body;
    auto file     = aMsg.get_part_by_name("file").body;

    auto table = aDBQ.getData<data::File>();

    std::string filepath =
        "assets/upload/" + std::to_string(table[0].num++) + "-" + filename;

    aDBQ.update<data::File>(table);

    auto file_handler = std::ofstream(filepath);
    file_handler << file;
    file_handler.close();

    return filepath;
}

