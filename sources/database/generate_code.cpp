#include "generate_code.hpp"

#include <fstream>
#include <string>

void
drawLine(std::ofstream& file)
{
    file << "\n";
    file << "//";
    for (int i = 0; i < 80; ++i) file << "-";
    file << "\n\n";
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

    std::ifstream database("database.data");
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
                file << "\tstatic std::unordered_map<std::string, uint8_t> "
                        "columnNames;\n";
                file << "\n\tvoid reset();\n";
                file << "};\n";
                temp        = "";
                columnCount = 0;

                file << "\nstruct " << structName
                     << " : public UpperDataStruct<" << baseName
                     << ">\n{\n};\n";
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
            bool flag = false;
            temp += "\t";
            if (s2 == "character")
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
                temp += "bool ";
            }
            else if (s2 == "date")
            {
                temp += "std::string ";
            }
            temp += s1;
            if (flag) temp += " = 0";
            temp += ";\n";
        }

        columnCount++;
        std::getline(database, s2);
    }

    file << "\n} // namespace data\n";

    drawLine(file);
    file << "#endif // !DATABASE_STRUCTURES_HPP\n";
}

void
generateDatabaseStructuresCPPFile()
{
    std::ofstream fileCPP("../sources/database/database_structures.cpp");
    // std::ofstream fileCPP("database_structures.cpp");
    fileCPP << "#include \"database_structures.hpp\"\n\n";
    fileCPP << "#include <cstring>\n\n";
    fileCPP << "#include \"core/core.hpp\"\n\n";

    std::ifstream database("database.data");
    std::string structName = "";
    std::string baseName   = "";
    std::string smallName  = "";
    int columnCount        = 0;
    std::string tempCPP;
    std::string columnNames = "{ {\"id\", 0},";
    std::string columnTypes = "{ data::Type::INT, ";
    while (true)
    {
        std::string s1, s2;
        database >> s1 >> s2;

        if (s1 == "TABLE")
        {
            if (columnCount)
            {
                columnNames.resize(columnNames.size() - 2);
                columnTypes.resize(columnTypes.size() - 2);
                columnCount = 0;

                fileCPP << "std::string data::" << baseName
                        << "::tableName         = \"" << smallName << "\";\n";
                fileCPP << "std::vector<data::Type> data::" << baseName
                        << "::types = " << columnTypes << "};\n";

                fileCPP << "std::unordered_map<std::string, uint8_t> "
                           "data::"
                        << baseName << "::columnNames = " << columnNames
                        << "};\n";

                fileCPP << "\nvoid\n";
                fileCPP << "data::" << baseName << "::reset()\n";
                fileCPP << "{\n";
                fileCPP << "\tptrs[0] = (void*)(&id);\n";
                fileCPP << tempCPP;
                fileCPP << "}\n\n";
                tempCPP     = "";
                columnNames = "{ {\"id\", 0},";
                columnTypes = "{ data::Type::INT, ";
            }

            if (s2 == "NUN") break;
            structName = s2;
            structName[0] += 'A' - 'a';
            baseName  = structName + "Base";
            smallName = s2;
        }
        else
        {
            if (s2 == "character")
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
            tempCPP += "\tptrs[";
            tempCPP += std::to_string(columnCount);
            tempCPP += "] = (void*)(&";
            tempCPP += s1;
            tempCPP += ");\n";

            columnNames += "{\"" + s1 + "\", ";
            columnNames += std::to_string(columnCount);
            columnNames += "}, ";
        }

        columnCount++;
        std::getline(database, s2);
    }
}

void
generateRequestHandlerFile()
{

    std::ofstream file("../sources/server/request_handler.hpp");
    // std::ofstream file("request_handler.hpp");

    file << "#ifndef REQUEST_HANDLER_HPP\n";
    file << "#define REQUEST_HANDLER_HPP\n";
    file << "\n";

    file << "#include \"core/grade_handler.hpp\" \n";
    file << "#include \"core/journal_handler.hpp\" \n";
    file << "#include \"core/plan_handler.hpp\" \n";
    file << "#include \"core/post_handler.hpp\" \n";

    file << "\n";

    file << "#define SERVER_FUNCTIONS \\\n";

    file << "    template <typename... Args> \\\n";
    file << "    crow::json::wvalue::list getDataAsJSON(std::string_view "
            "aTableName, \\\n";
    file
        << "                                     Args&&... args) noexcept \\\n";
    file << "    { \\\n";
    file << "        crow::json::wvalue::list res{400}; \\\n";
    file << "        auto hasher   = std::hash<std::string_view>{}; \\\n";
    file << "        auto str_hash = hasher(aTableName); \\\n \\\n";

    std::ifstream database("database.data");
    std::string temp;

    bool flag = true;
    while (true)
    {
        std::string s1, s2;
        if (!(database >> s1)) break;
        getline(database, s2, ' ');
        getline(database, s2);

        if (s1 == "TABLE" && s2 != "NUN")
        {
            std::string structName = s2;
            structName[0] += 'A' - 'a';

            if (flag)
            {
                file << "        if";
                temp += "        if";
            }
            else
            {
                file << "        else if";
                temp += "        else if";
            }
            flag = false;

            file << " (str_hash == hasher(\"" << s2 << "\")) \\\n";
            file << "        { \\\n";
            file << "            res = getData<data::" << structName
                 << ">(args...); \\\n";
            file << "        } \\\n";

            temp += " (str_hash == hasher(\"" + s2 + "\")) \\\n";
            temp += "        { \\\n";
            temp += "            res = core::PostHandler::process<data::" +
                    structName + ">(args...); \\\n";
            temp += "        } \\\n";
        }
    }

    file << "\\\n        return res; \\\n    } \\\n\\\n";

    file << "    template <typename... Args> \\\n";
    file << "    crow::json::wvalue postRequestHandler(std::string_view "
            "aTableName, \\\n";
    file << "                            Args&&... args) "
            "noexcept \\\n";
    file << "    { \\\n";
    file << "        crow::json::wvalue res{400}; \\\n";
    file << "        auto hasher   = std::hash<std::string_view>{}; \\\n";
    file << "        auto str_hash = hasher(aTableName); \\\n \\\n";

    file << temp;
    file << "\\\n        return res; \\\n     }\n";

    file << "#endif // !REQUEST_HANDLER_HPP\n";
}

void
generateAsteriskHendler()
{

    std::ofstream file("../sources/server/asterisk_hendler.hpp");
    // std::ofstream file("request_handler.hpp");

    file << "#ifndef ASTERISK_HENDLER_HPP\n";
    file << "#define ASTERISK_HENDLER_HPP\n";
    file << "\n";
    file << "#include <string>\n";
    file << "#include <vector>\n";
    file << "#include <unordered_map>\n";
    file << "\n";
    file << "struct AsteriskHendler\n";
    file << "{ \n";

    file << "    static std::unordered_map<std::string_view, "
            "std::vector<std::string>> "
            "table;\n";

    file << "};\n\n";
    file << "#endif // !ASTERISK_HENDLER_HPP\n";

    file.close();

    file.open("../sources/server/asterisk_hendler.cpp");
    std::ifstream database("database.data");
    file << "#include \"asterisk_hendler.hpp\"\n\n";
    file << "std::unordered_map<std::string_view, std::vector<std::string>> "
            "AsteriskHendler::table = \n{\n";

    std::string temp;
    while (true)
    {
        std::string s1, s2;
        database >> s1;
        getline(database, s2, ' ');
        getline(database, s2);
        if (s2 == "NUN") break;

        if (s1 == "TABLE")
        {
            temp += "}}, { \"" + s2 + "\", { \"id\", ";
        }
        else
        {
            temp += "\"" + s1 + "\", ";
        }
    }
    temp[0] = ' ';
    temp[1] = ' ';
    temp[2] = ' ';

    temp[temp.size() - 2] = ' ';
    temp += "}}};";

    file << temp;

    file << "\n";
}

void
data::generateDatabaseStructuresFiles()
{
    generateDatabaseStructuresHPPFile();
    generateDatabaseStructuresCPPFile();
    generateRequestHandlerFile();
    generateAsteriskHendler();
}
