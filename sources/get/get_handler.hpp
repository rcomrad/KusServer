#ifndef GET_HANDLER_HPP
#define GET_HANDLER_HPP

//--------------------------------------------------------------------------------

#include "database/data_request.hpp"
#include "database/database_query.hpp"

#include "crow.h"

//--------------------------------------------------------------------------------

namespace get
{
class GetHandler
{
public:
    static crow::json::wvalue mainGet(const std::string& aRequest,
                                      const std::string& aCondition,
                                      data::DBSettings& aDBS) noexcept
    {
        crow::json::wvalue result;
        data::DataRequest req(aRequest, aCondition);
        for (const auto& i : req)
        {
            transmitter(i, aDBS);
        }
        return result;
    }

    template <typename... Args>
    static crow::json::wvalue process(const data::TableInfoAray& request,
                                      data::DBSettings& aDBS,
                                      Args&&... args) noexcept
    {
        // auto tabl = request.getTables();
        // auto col  = request.getColumns();
        // auto con  = request.getCondition();

        crow::json::wvalue result;

        data::DatabaseQuery dbq(aDBS);
        dbq.select(request, args...);

        ([&] { args; }(), ...);

        return result;
    }

private:
    static void transmitter(const data::TableInfoAray& request,
                            data::DBSettings& aDBS);
    static void transmitter(const std::string& aTableName, void* aTable);

    //     template <typename... Args>
    //     void makeDataRequest(data::DataRequest& aRequest,
    //                          int num1,
    //                          int num2,
    //                          const std::string& aCondition,
    //                          Args&&... args) noexcept
    //     {
    //         if (num2 >= aRequest.request[num1].size())
    //         {
    //             х
    //         }
    //         else
    //         {
    //             data::DatabaseQuery dbq(mDBS);
    //             dbq.getData(aRequest, num1, aCondition, args...);
    //         }
    //     }

    //     {
    //         crow::json::wvalue res;

    //         for (auto& i : table)
    //         {
    //             crow::json::wvalue temp;
    //             // for (auto& j : table.names)
    //             for (auto& j : aRequest)
    //             {
    //                 std::string name(j.first);
    //                 if (name == "*") continue;
    //                 // size_t indx      = j.second;

    //                 // auto opt         = aRequest[name];
    //                 // if (!opt.has_value()) continue;

    //                 auto it    = table.names.find(name);
    //                 bool notID = false;
    //                 if (it == table.names.end())
    //                 {
    //                     it    = table.names.find("id");
    //                     notID = true;
    //                 }
    //                 size_t indx = it->second;

    //                 // if (name == "role_id" || opt.get().second.size() > 1)
    //                 if (name == "role_id")
    //                 {
    //                     temp["role"] =
    //                         getDataAsJSON("role", GetRequest(),
    //                                       "id = " +
    //                                       data::wrap(*(int*)i[indx]));
    //                 }
    //                 // else
    //                 else if (j.second.size() > 0)
    //                 {
    //                     bool kostil = false;
    //                     if (name == "group_id" && !*(bool*)i[3])
    //                     {
    //                         name   = "grade_id";
    //                         kostil = true;
    //                     }

    //                     std::string cond = "id = ";
    //                     if (!notID) name.resize(name.size() - 3);
    //                     else
    //                     {
    //                         cond = aRequest.name;
    //                         cond += "_id = "s;
    //                     }
    //                     auto req = GetRequest(j.second, name);

    //                     auto jList = getDataAsJSON(
    //                         req.name, req, cond +
    //                         data::wrap(*(int*)i[indx]));

    //                     if (kostil) name = "group";
    //                     if (jList.size() != 1)
    //                     {
    //                         temp[name + "s"] = std::move(jList);
    //                     }
    //                     else
    //                     {
    //                         temp[name] = std::move(jList[0]);
    //                     }
    //                 }
    //                 else
    //                 {
    //                     switch (table.types[indx])
    //                     {
    //                         case data::Type::INT:
    //                             temp[name] = *(int*)i[indx];
    //                             break;
    //                         case data::Type::BOOL:
    //                             temp[name] = *(bool*)i[indx];
    //                             break;
    //                         case data::Type::CHARS:
    //                             temp[name] = std::string((char*)i[indx]);
    //                             break;
    //                         case data::Type::STRING:
    //                             temp[name] = *(std::string*)i[indx];
    //                             break;
    //                     }
    //                 }
    //             }

    //             if (!aSecondCondition.empty())
    //             {
    //                 auto ansTable = dbq.getData<data::User_answer>(
    //                     aSecondCondition +
    //                     " AND question_id = " + std::to_string(i.id));

    //                 if (ansTable.size())
    //                 {
    //                     temp["user_answer"] = ansTable.back().user_answer;
    //                 }
    //             }

    //             res.emplace_back(std::move(temp));
    //         }
    //     }
    //     return res;
    // }

    // //--------------------------------------------------------------------------------

    // crow::json::wvalue::list
    // getDataHendler(const std::string& aRequest, std::string&& aCondition)
    // noexcept
    // {
    //     for (auto& i : aCondition)
    //     {
    //         if (i == ';') i = ' ';
    //     }
    //     GetRequest req(aRequest);
    //     if (req.args.size() == 0)
    //     {
    //         req.args["*"];
    //     }
    //     req.reset(req.name);
    //     return getDataAsJSON(req.name, req, aCondition);
    // }

    // crow::response
    // get(const std::string& aRequest,
    //     std::string&& aCondition,
    //     const std::string& aSecondCondition = "") noexcept
    // {
    //     bool flag = true;
    //     if (aCondition[0] == '~')
    //     {
    //         flag          = false;
    //         aCondition[0] = ' ';
    //     }

    //     for (auto& i : aCondition)
    //     {
    //         if (i == ';') i = ' ';
    //     }
    //     GetRequest req(aRequest);
    //     if (req.args.size() == 0)
    //     {
    //         req.args["*"];
    //     }
    //     req.reset(req.name);
    //     auto data = getDataAsJSON(req.name, req, aCondition,
    //     aSecondCondition);

    //     crow::response res;
    //     if (data.size() == 0)
    //     {
    //         res = std::move(crow::response{401});
    //     }
    //     else
    //     {
    //         crow::json::wvalue temp;
    //         std::string tempName(req.name);
    //         if (flag)
    //         {
    //             tempName += "s";
    //             temp[tempName] = std::move(data);
    //         }
    //         else
    //         {
    //             temp[tempName] = std::move(data[0]);
    //         }

    //         // crow::json::wvalue
    //         //     temp[data.size() > 1 ? "s" + std::string(req.name) :
    //         //     req.name] =
    //         //         data;
    //         res = std::move(temp);
    //     }

    //     return res;
    // }
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !GET_HANDLER_HPP
