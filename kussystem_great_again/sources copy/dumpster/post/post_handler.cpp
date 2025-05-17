#include "post_handler.hpp"

#include "domain/date_and_time.hpp"

#include "core/file_router.hpp"

#include "database/connection_manager.hpp"
#include "database/safe_sql_wrapper.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"

#include "post_router.hpp"

//--------------------------------------------------------------------------------

crow::json::wvalue
post::PostHandler::manyToMany(
    int aID,
    const char* aTableName,
    ManyToMany& aType,
    std::unordered_map<str::String, crow::json::rvalue> aLeftovers) noexcept
{
    crow::json::wvalue res;

    str::String id = data::safeWrap(aID);

    for (auto& other : aLeftovers)
    {
        if (!(other.second.t() == crow::json::type::List &&
              other.second[0].t() == crow::json::type::Number))
        {
            continue;
        }
        data::RawData data;
        data.header["partly"] = "true";
        auto& value           = data.value;

        bool flag = aTableName < other.first;

        // TODO:
        // value.reserve(other.second.size());
        for (auto& i : other.second)
        {
            value.emplace_back();
            if (flag)
            {
                value.back().emplace_back(id);
                value.back().emplace_back(std::to_string(i.i()));
            }
            else
            {
                value.back().emplace_back(std::to_string(i.i()));
                value.back().emplace_back(id);
            }
        }

        str::String mtmTable;
        mtmTable.reserve(aTableName.size() + other.first.size() + 1);
        mtmTable += flag ? aTableName : other.first;
        mtmTable.push_back('_');
        mtmTable += !flag ? aTableName : other.first;

        if (int(aType) & int(ManyToMany::Delete))
        {
            auto connection = data::ConnectionManager::getUserConnection();
            connection.val.drop(mtmTable,
                                aTableName + "_id=" + std::to_string(aID));
        }
        if (int(aType) & int(ManyToMany::Add))
        {
            post::PostRouter::rawDataRouter(mtmTable, data);
        }
    }

    return res;
}

//--------------------------------------------------------------------------------

crow::json::wvalue
post::PostHandler::uploadFromFile(
    std::unordered_map<str::String, str::String>&& aHeader,
    const char* aFileName) noexcept
{
    auto data = core::FileRouter::process(aFileName);

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
post::PostHandler::uploadFromFileRequest(const char* aType,
                                         const crow::request& aReq) noexcept
{
    LOG_INFO("Start upload");

    crow::multipart::message msg(aReq);
    str::String filePath = uploadFile(msg);

    std::unordered_map<str::String, str::String> header = {
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

#include "server/request_unpacker.hpp"

// TODO: use file.hpp
str::String
post::PostHandler::uploadFile(crow::multipart::message& aMsg,
                              const char* aFileKey,
                              const char* aFilenameKey) noexcept
{
    LOG_INFO("File upload func");

    auto pathPrefix = core::Path::getPathUnsafe("upload");
    // LOG_INFO("File prefix:", pathPrefix);

    str::String fileName;
    if (!aFilenameKey.empty())
        fileName = serv::RequestUnpacker::getPartUnsafe(aMsg, aFilenameKey);
    // LOG_INFO("File name:", fileName);
    auto file = serv::RequestUnpacker::getPartUnsafe(aMsg, aFileKey);
    // LOG_INFO("File data:", file);

    str::String filePath =
        pathPrefix + dom::DateAndTime::getCurentTimeSafe() + "-" + fileName;
    file::File::writeData(filePath, file);

    return filePath;
}

void
post::PostHandler::setRawData(std::vector<std::vector<str::String>>& aData,
                              int aNum,
                              const char* aTableName,
                              const char* aColumnName) noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();
    for (auto& i : aData)
    {
        i.push_back(
            connection.val.getCell(aTableName, aColumnName, "id=" + i[aNum]));
    }
}
