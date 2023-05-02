#include "generate_code.hpp"

#include <fstream>
#include <map>
#include <string>

std::unordered_map<std::string, std::string> core::GenerateCode::mglobalPaths =
    {
        {"post", "../sources/post/"},
        {"get",  "../sources/get/" }
};

std::vector<std::string> core::GenerateCode::mDatabaseTables =
    core::GenerateCode::getDatabaseTables();

void
drawLine(std::ofstream& file)
{
    file << "\n";
    file << "//";
    for (int i = 0; i < 80; ++i) file << "-";
    file << "\n\n";
}

void
core::GenerateCode::setClassName(const std::string& aName)
{
    mClassName = aName;

    mClassName[0] -= 'A' - 'a';
    for (auto i : mClassName)
    {
        if (i >= 'A' && i <= 'Z')
        {
            mFileName.push_back('_');
            mDefineName.push_back('_');
            i -= 'A' - 'a';
        }

        mFileName.push_back(i);
        i += 'A' - 'a';
        mDefineName.push_back(i);
    }
    mClassName[0] += 'A' - 'a';
}

void
core::GenerateCode::setNamespace(const std::string& aName)
{
    mNamespace = aName;
    mPath      = mglobalPaths[mNamespace];
}

void
core::GenerateCode::setDefaultTemplate(const std::string& aDefaultTemplate)
{
    mDefaultTemplate = aDefaultTemplate;
}

void
core::GenerateCode::setDefaultReturnType(const std::string& aDefaultReturnType)
{
    mDefaultReturnType = aDefaultReturnType;
}

void
core::GenerateCode::setDefaultResultBegin(
    const std::string& aDefaultResultBegin)
{
    mDefaultResultBegin = aDefaultResultBegin;
}

void
core::GenerateCode::setDefaultResultEnd(const std::string& aDefaultResultEnd)
{
    mDefaultResultEnd = aDefaultResultEnd;
}

void
core::GenerateCode::addInclude(const std::string& aInclude, bool aIsSTD)
{
    if (aIsSTD) mIncludes.insert("<" + aInclude + ">\n");
    else mIncludes.insert("\"" + aInclude + ".hpp\"\n");
}

void
core::GenerateCode::addCPPInclude(const std::string& aInclude, bool aIsSTD)
{
    if (aIsSTD) mCPPIncludes.insert("<" + aInclude + ">\n");
    else mCPPIncludes.insert("\"" + aInclude + ".hpp\"\n");
}

// void
// core::GenerateCode::addFunction(const std::string& aTemplate,
//                                 const std::string& aReturnType,
//                                 const std::string& aSignature,
//                                 const std::string& aBody)
// {
//     const std::string* templ = &aTemplate;
//     if (aTemplate.empty())
//     {
//         templ = &mDefaultTemplate;
//     }

//     const std::string* retur = &aReturnType;
//     if (aReturnType.empty())
//     {
//         retur = &mDefaultReturnType;
//     }

//     mFunctions.emplace_back(
//         std::vector<std::string>{*templ, *retur, aSignature, aBody});
// }

void
core::GenerateCode::pushBackFunction(const std::string& aSignature)
{
    mFunctions.emplace_back();

    mFunctions.back()._template   = mDefaultTemplate;
    mFunctions.back().returnType  = mDefaultReturnType;
    mFunctions.back().signature   = aSignature;
    mFunctions.back().resultBegin = mDefaultResultBegin;
    mFunctions.back().resultEnd   = mDefaultResultEnd;
}

void
core::GenerateCode::pushToFunctionBody(const std::string& aBody)
{
    mFunctions.back().body += aBody;
}

void
core::GenerateCode::generateElseIfTable(
    const std::unordered_map<std::string, std::string>& aGotoTable)
{
    std::string& temp = mFunctions.back().body;

    bool flag = true;
    bool specialTreatment;
    for (auto& name : mDatabaseTables)
    {
        auto it = aGotoTable.find(name);
        if (it == aGotoTable.end())
        {
            it               = aGotoTable.find("default");
            specialTreatment = false;
        }
        else
        {
            specialTreatment = true;
        }
        const std::string& funkName = it->second;

        std::string structName = name;
        structName[0] += 'A' - 'a';

        if (flag)
        {
            temp += "        if";
            flag = false;
        }
        else
        {
            temp += "        else if";
        }
        temp += " (str_hash == hasher(\"" + name + "\")) \n";
        temp += "{ \n";
        temp += "res = " + funkName;
        if (!specialTreatment) temp += structName + ">";
        temp += "(args...); \n";
        temp += " } \n";
    }
}

void
core::GenerateCode::generateMapTable(
    const std::string& aName,
    const std::unordered_map<std::string, std::string>& aGotoTable,
    bool aAddTemplate)
{
    addInclude("unordered_map", true);

    mStaticVariables.emplace_back();
    mStaticVariables.back().name = aName;
    mStaticVariables.back().type =
        "std::unordered_map<std::string, decltype(&" +
        aGotoTable.find("default")->second + "Dummy>)>";

    std::string& temp = mStaticVariables.back().initialisation;

    bool flag = false;
    bool specialTreatment;

    temp += "{";
    for (auto& name : mDatabaseTables)
    {
        auto it = aGotoTable.find(name);
        if (it == aGotoTable.end())
        {
            it               = aGotoTable.find("default");
            specialTreatment = false;
        }
        else
        {
            specialTreatment = true;
        }
        const std::string& funkName = it->second;

        std::string structName = name;
        structName[0] += 'A' - 'a';

        if (flag) temp += ",";
        temp += "{";
        temp += "\"" + name + "\"";
        temp += ", &";
        temp += funkName;
        if (!specialTreatment || aAddTemplate) temp += structName + ">";
        temp += "}";

        flag = true;
        // temp += "(args...); \n";
        // temp += " } \n";
    }
    temp += "};";
}

void
core::GenerateCode::write()
{
    writeHPP();
    writeCPP();
}

void
core::GenerateCode::writeHPP()
{
    std::ofstream hppFle(mPath + mFileName + ".hpp");

    hppFle << "#ifndef " + mDefineName + "_HPP\n";
    hppFle << "#define " + mDefineName + "_HPP\n";
    hppFle << "\n";

    for (auto& i : mIncludes)
    {
        hppFle << "#include " + i;
    }
    hppFle << "\n";

    hppFle << "namespace " + mNamespace + "\n";
    hppFle << "{ \n";
    hppFle << "class " + mClassName + "\n";
    hppFle << "{ \n";
    hppFle << "public: \n";

    for (auto& funk : mFunctions)
    {
        hppFle << funk.getDeclaration() << "\n\n";
    }

    hppFle << "private: \n";
    for (auto& i : mStaticVariables)
    {
        hppFle << i.getDeclaration() << "\n";
    }

    hppFle << "\n};\n";
    hppFle << "\n} // namespace " << mNamespace << "\n";
    hppFle << "#endif // !" << mDefineName << "\n";

    hppFle.close();
}

void
core::GenerateCode::writeCPP()
{
    std::ofstream cppFle(mPath + mFileName + ".cpp");

    cppFle << "#include \"" << mFileName + ".hpp\"";
    cppFle << "\n\n";

    for (auto& i : mCPPIncludes)
    {
        cppFle << "#include " + i;
    }
    cppFle << "\n\n";

    for (auto& i : mStaticVariables)
    {
        cppFle << i.getInitialisation(mNamespace, mClassName) << "\n\n";
    }

    for (auto& funk : mFunctions)
    {
        cppFle << funk.getInitialisation(mNamespace, mClassName) << "\n\n";
    }

    cppFle << "\n";
    cppFle.close();
}

std::vector<std::string>
core::GenerateCode::getDatabaseTables()
{
    std::vector<std::string> res;

    std::ifstream database("database.psql_db");
    while (true)
    {
        std::string s1, s2;
        if (!(database >> s1)) break;
        getline(database, s2, ' ');
        getline(database, s2);

        if (s1 == "TABLE" && s2 != "NUN")
        {
            res.push_back(s2);
        }
    }

    return res;
}

void
generateDatabaseStructuresHPPFile()
{
    std::ofstream file("../sources/database/database_structures.hpp");

    file << "#ifndef DATABASE_STRUCTURES_HPP\n";
    file << "#define DATABASE_STRUCTURES_HPP\n";

    drawLine(file);
    file << "#include \"database_wrappers.hpp\"\n";
    drawLine(file);
    file << "namespace data\n{\n";

    std::ifstream database("database.psql_db");
    std::string structName = "";
    std::string baseName   = "";
    std::string smallName  = "";
    int columnCount        = 0;
    std::string temp;
    while (true)
    {
        std::string s1, s2;
        database >> s1 >> s2;

        if (s1 == "TABLE")
        {
            if (columnCount)
            {
                file << " : public BaseDataStruct<" << columnCount << ">\n{\n";
                file << "\tint id = 0;\n";
                file << temp << "\n";
                file << "\tstatic std::string tableName;\n";
                file << "\tstatic std::vector<data::Type> types;\n";
                file << "\tstatic std::vector<std::string> names;\n";
                file << "\tstatic std::unordered_map<std::string, uint8_t> "
                        "nameToNum;\n";
                file << "\n\tvoid reset();\n";
                file << "};\n";
                temp        = "";
                columnCount = 0;

                file << "\nusing " << structName << " = UpperDataStruct<"
                     << baseName << ">;\n\n";
            }

            if (s2 == "NUN") break;
            structName = s2;
            structName[0] += 'A' - 'a';
            baseName  = structName + "Base";
            smallName = s2;
            file << "\nstruct " << baseName;
        }
        else
        {
            bool flag   = false;
            bool flagGG = false;
            temp += "\t";
            if (s2 == "character")
            {
                temp += "std::string ";
            }
            else if (s2 == "text")
            {
                temp += "std::string ";
            }
            else if (s2 == "integer")
            {
                temp += "int ";
                flag = true;
            }
            else if (s2 == "smallint")
            {
                temp += "int ";
                flag = true;
            }
            else if (s2 == "boolean")
            {
                temp += "char ";
                flagGG = true;
            }
            else if (s2 == "date")
            {
                temp += "std::string ";
            }
            else if (s2 == "timestamp")
            {
                temp += "std::string ";
            }
            temp += s1;
            if (flag) temp += " = 0";
            if (flagGG) temp += " = -1";
            temp += ";\n";
        }

        columnCount++;
        std::getline(database, s2);
    }

    file << "\n} // namespace data\n";

    drawLine(file);
    file << "#endif // !DATABASE_STRUCTURES_HPP\n";

    // file << "#ifndef ASTERISK_HENDLER_HPP\n";
    // file << "#define ASTERISK_HENDLER_HPP\n";
    // file << "\n";
    // file << "#include <string>\n";
    // file << "#include <vector>\n";
    // file << "#include <unordered_map>\n";
    // file << "\n";
    // file << "struct AsteriskHendler\n";
    // file << "{ \n";

    // file << "    static std::unordered_map<std::string_view, "
    //         "std::vector<std::string>> "
    //         "table;\n";

    // file << "};\n\n";
    // file << "#endif // !ASTERISK_HENDLER_HPP\n";

    // file.close();
}

void
generateDatabaseStructuresCPPFile()
{
    std::ofstream fileCPP("../sources/database/database_structures.cpp");
    // std::ofstream fileCPP("database_structures.cpp");
    fileCPP << "#include \"database_structures.hpp\"\n\n";
    fileCPP << "#include <cstring>\n\n";

    std::ifstream database("database.psql_db");
    std::string structName = "";
    std::string baseName   = "";
    std::string smallName  = "";
    int columnCount        = 0;
    std::string tempCPP;
    std::string columnNames     = "{ {\"id\", 0}, ";
    std::string columnTypes     = "{ data::Type::INT, ";
    std::string columnNamesTrue = "{ \"id\", ";
    std::string temp;
    while (true)
    {
        std::string s1, s2;
        database >> s1 >> s2;

        if (s1 == "TABLE")
        {
            temp += "}}, { \"" + s2 + "\", { \"id\", ";
            if (columnCount)
            {
                columnNames.resize(columnNames.size() - 2);
                columnTypes.resize(columnTypes.size() - 2);
                columnNamesTrue.resize(columnNamesTrue.size() - 2);
                columnCount = 0;

                fileCPP << "std::string data::" << baseName
                        << "::tableName         = \"" << smallName << "\";\n";
                fileCPP << "std::vector<data::Type> data::" << baseName
                        << "::types = " << columnTypes << "};\n";
                fileCPP << "std::vector<std::string> data::" << baseName
                        << "::names = " << columnNamesTrue << "};\n";

                fileCPP << "std::unordered_map<std::string, uint8_t> "
                           "data::"
                        << baseName << "::nameToNum = " << columnNames
                        << "};\n";

                fileCPP << "\nvoid\n";
                fileCPP << "data::" << baseName << "::reset()\n";
                fileCPP << "{\n";
                fileCPP << "\tptrs[0] = (void*)(&id);\n";
                fileCPP << tempCPP;
                fileCPP << "}\n\n";
                tempCPP         = "";
                columnNames     = "{ {\"id\", 0},";
                columnTypes     = "{ data::Type::INT, ";
                columnNamesTrue = "{ \"id\", ";
            }

            if (s2 == "NUN") break;
            structName = s2;
            structName[0] += 'A' - 'a';
            baseName  = structName + "Base";
            smallName = s2;
        }
        else
        {
            temp += "\"" + s1 + "\", ";

            if (s2 == "character")
            {
                columnTypes += "data::Type::STRING, ";
            }
            else if (s2 == "text")
            {
                columnTypes += "data::Type::STRING, ";
            }
            else if (s2 == "integer")
            {
                columnTypes += "data::Type::INT, ";
            }
            else if (s2 == "smallint")
            {
                columnTypes += "data::Type::INT, ";
            }
            else if (s2 == "boolean")
            {
                columnTypes += "data::Type::BOOL, ";
            }
            else if (s2 == "date")
            {
                columnTypes += "data::Type::STRING, ";
            }
            else if (s2 == "timestamp")
            {
                columnTypes += "data::Type::STRING, ";
            }
            tempCPP += "\tptrs[";
            tempCPP += std::to_string(columnCount);
            tempCPP += "] = (void*)(&";
            tempCPP += s1;
            tempCPP += ");\n";

            columnNames += "{\"" + s1 + "\", ";
            columnNames += std::to_string(columnCount);
            columnNames += "}, ";

            columnNamesTrue += "\"" + s1 + "\", ";
        }

        columnCount++;
        std::getline(database, s2);
    }

    // fileCPP << "std::unordered_map<std::string_view,
    // std::vector<std::string>> "
    //            "AsteriskHendler::table = \n{\n";

    // temp[0] = ' ';
    // temp[1] = ' ';
    // temp[2] = ' ';

    // temp[temp.size() - 2] = ' ';
    // temp += "}}};";

    // fileCPP << temp;

    // fileCPP << "\n";

    fileCPP.close();
}

std::string
wrap(std::string aname)
{
    return "crow::json::wvalue result;\n"
           "auto it = " +
           aname +
           ".find(aTableName);\n"
           "if (it != " +
           aname +
           ".end())\n"
           "result= it->second(args...);return result;\n";
}

void
generateGetRouterFile()
{
    //     core::GenerateCode generator;
    //     generator.setClassName("GetRouter");
    //     generator.setNamespace("get");

    //     //--------------------------------------------------------------------------------

    //     generator.setDefaultTemplate("template <typename... Args>");
    //     generator.setDefaultReturnType("void");

    //     //--------------------------------------------------------------------------------

    //     generator.addInclude("get_handler");

    //     //--------------------------------------------------------------------------------

    //     // postHandler
    //     // generator.p
    //     generator.pushBackFunction("getRouter(const data::TableInfoAray&
    //     request, "
    //                                "data::DBSettings& aDBS, "
    //                                "Args&&... args) noexcept");

    //     generator.pushToFunctionBody(
    //         "auto temp = request.popTableName();\n"
    //         "if (temp){\n"
    //         "getRouter(request, aDBS, args..., );\n"
    //         "}\n"
    //         "else{\n"
    //         "get::GetHandler::process(request, aDBS, args...);\n"
    //         "}\n"

    //     );

    //     generator.write();

    core::GenerateCode generator;
    generator.setClassName("GetRouter");
    generator.setNamespace("get");

    //--------------------------------------------------------------------------------

    generator.setDefaultTemplate("template <typename... Args>");
    generator.setDefaultReturnType("static crow::json::wvalue");

    //--------------------------------------------------------------------------------

    generator.addInclude("get_handler");
    generator.addCPPInclude("user_handler");
    generator.addCPPInclude("question_handler");

    //--------------------------------------------------------------------------------

    // basicRouter
    generator.pushBackFunction("basicRouter(const std::string& aTableName, "
                               "Args&&... args) noexcept");
    generator.pushToFunctionBody(wrap("mBasicRouterMap"));
    generator.generateMapTable(
        "mBasicRouterMap",
        {
            {"default", "get::GetHandler::process<data::"},
            {"user",    "get::UserHandler::process"      }
  //    ,
  //    {"question", "get::QuestionHandler::process"  }
    });

    //--------------------------------------------------------------------------------

    // dumpRouter
    generator.pushBackFunction("dumpRouter(const std::string& aTableName, "
                               "Args&&... args) noexcept");
    generator.pushToFunctionBody(wrap("mDumpRouterMap"));
    generator.generateMapTable(
        "mDumpRouterMap", {
                              {"default", "get::GetHandler::dump<data::"}
    });

    //--------------------------------------------------------------------------------

    generator.write();
}

void
generatePostHandlerFile()
{

    core::GenerateCode generator;
    generator.setClassName("PostRouter");
    generator.setNamespace("post");

    //--------------------------------------------------------------------------------

    generator.setDefaultTemplate("template <typename... Args>");
    generator.setDefaultReturnType("static crow::json::wvalue");

    //--------------------------------------------------------------------------------

    generator.addInclude("post_handler");
    generator.addCPPInclude("answer_handler");
    generator.addCPPInclude("journal_handler");
    generator.addCPPInclude("plan_handler");
    generator.addCPPInclude("user_handler");
    generator.addCPPInclude("mark_handler");

    //--------------------------------------------------------------------------------

    // basicHandler
    generator.pushBackFunction("basicRouter(const std::string& aTableName, "
                               "Args&&... args) noexcept");
    generator.pushToFunctionBody(wrap("mPostRouterMap"));
    generator.generateMapTable(
        "mPostRouterMap",
        {
  // clang-format off
            {"default",       "post::PostHandler::basicPost<post::PostHandler, data::"},
            {"user",          "post::PostHandler::basicPost<post::UserHandler, data::"       },
            {"answer",        "post::PostHandler::basicPost<post::AnswerHandler, data::"     },
            {"journal_table", "post::PostHandler::basicPost<post::JournalHandler, data::"    },
            {"mark",          "post::PostHandler::basicPost<post::MarkHandler, data::"       }
  // clang-format on
    },
        true);

    //--------------------------------------------------------------------------------

    // // manyToManyHandler
    // generator.pushBackFunction(
    //     "manyToManyRouter(const std::string& aTableName, "
    //     "Args&&... args) noexcept");
    // generator.pushToFunctionBody(wrap("mManyToManyRouterMap"));
    // generator.generateMapTable(
    //     "mManyToManyRouterMap",
    //     {
    //         {"default", "post::PostHandler::manyToMany<data::"}
    // });

    //--------------------------------------------------------------------------------

    // // uploadPostHandler
    // generator.pushBackFunction("uploadRouter(const std::string& aTableName, "
    //                            "Args&&... args) noexcept");
    // generator.pushToFunctionBody(wrap("mUploadRouterMap"));
    // generator.generateMapTable(
    //     "mUploadRouterMap",
    //     {
    //         {"default",       "post::PostHandler::uploadFromFile<data::"},
    //         {"journal_table", "post::JournalHandler::uploadFromFile"    },
    //         {"user",          "post::UserHandler::uploadFromFile"       },
    //         {"plan",          "post::PlanHandler::uploadFromFile"       }
    // });

    //--------------------------------------------------------------------------------

    // dropHandler
    generator.pushBackFunction("dropRouter(const std::string& aTableName, "
                               "Args&&... args) noexcept");
    generator.pushToFunctionBody(wrap("mDropRouterMap"));
    generator.generateMapTable(
        "mDropRouterMap", {
                              {"default", "post::PostHandler::drop<data::"}
    });

    //--------------------------------------------------------------------------------

    // rawDataHandler
    generator.pushBackFunction("rawDataRouter(const std::string& aTableName, "
                               "Args&&... args) noexcept");
    generator.pushToFunctionBody(wrap("mRawDataRouter"));
    generator.generateMapTable(
        "mRawDataRouter",
        {
            {"default",       "post::PostHandler::rawDataHandler<data::"},
            {"journal_table", "post::JournalHandler::rawDataHandler"    },
            {"user",          "post::UserHandler::rawDataHandler"       },
            {"plan",          "post::PlanHandler::rawDataHandler"       }
    });

    //--------------------------------------------------------------------------------

    // // headerHandler
    // generator.pushBackFunction("headerRouter(const std::string& aTableName, "
    //                            "Args&&... args) noexcept");
    // generator.pushToFunctionBody(wrap("mHeaderRouter"));
    // generator.generateMapTable(
    //     "mHeaderRouter",
    //     {
    //         {"default", "post::PostHandler::headerParser<data::"},
    //         {"plan",    "post::PlanHandler::headerParser"       }
    // });

    //--------------------------------------------------------------------------------

    generator.write();
}

void
core::generateDatabaseStructuresFiles()
{
    // generateDatabaseStructuresHPPFile();
    // generateDatabaseStructuresCPPFile();

    // generatePostHandlerFile();
    // generateGetRouterFile();
}
