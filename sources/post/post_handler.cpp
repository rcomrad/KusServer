#include "post_handler.hpp"

#include "database/connection_manager.hpp"

#include "file/path.hpp"

#include "post_router.hpp"

//--------------------------------------------------------------------------------

crow::json::wvalue
post::PostHandler::uploadFromFile(
    std::unordered_map<std::string, std::string>&& aHeader,
    const std::string& aFileName) noexcept
{
    auto data = file::FileRouter::process(aFileName);

    if (aHeader["type"] == "nun")
    {
        for (auto& i : data)
        {
            PostRouter::rawDataRouter(i.first, i.second);
        }
    }
    else
    {
        aHeader["url"]              = aFileName;
        data.begin()->second.header = std::move(aHeader);
        PostRouter::rawDataRouter(data.begin()->second.header["type"],
                                  data.begin()->second);
    }

    return {200};
}

crow::json::wvalue
post::PostHandler::uploadFromFileRequest(const std::string& aType,
                                         const crow::request& aReq) noexcept
{
    crow::multipart::message msg(aReq);
    std::string filePath = uploadFile(msg);

    std::unordered_map<std::string, std::string> header = {
        {"type", aType}
    };
    for (auto& i : msg.part_map)
    {
        if (i.first != "filename" && i.first != "file")
        {
            header[i.first] = i.second.body;
        }
    }

    return uploadFromFile(std::move(header), filePath);
}

//--------------------------------------------------------------------------------

// TODO: use file.hpp
std::string
post::PostHandler::uploadFile(crow::multipart::message& aMsg,
                              std::string aPathPrefix) noexcept
{
    if (aPathPrefix.empty())
        aPathPrefix = file::Path::getInstance().getPath("upload").value();

    // TODO: filename
    auto fileName = aMsg.get_part_by_name("filename").body;
    auto file     = aMsg.get_part_by_name("file").body;

    std::string filePath;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        auto table      = connection.val.getData<data::File>();
        filePath = aPathPrefix + std::to_string(table.num++) + "-" + fileName;
        connection.val.update<data::File>(table);
    }

    auto file_handler = std::ofstream(filePath);
    if (file_handler.is_open())
    {
        file_handler << file;
        file_handler.close();
    }

    return filePath;
}

// void
// post::PostHandler::transmitToMTMHandler(const std::string aTableName,
//                                         int aID,
//                                         bool aIsAdding,
//                                         std::vector<int> aIDForInsert,
//                                         const std::string aTrueNam) noexcept
// {
//     PostRouter::manyToManyRouter(aTableName, aID, aIsAdding, aIDForInsert,
//                                  aTrueNam);
// }
