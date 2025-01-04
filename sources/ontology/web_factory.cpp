#include "web_factory.hpp"

#include <fstream>

#include "utility/file_system/path_storage.hpp"
#include "utility/string/parser.hpp"

#include "decoder.hpp"

//--------------------------------------------------------------------------------

static auto
readDefaultNodes() noexcept
{
    auto path =
        util::PathStorage::getFilePath("config", "ontology_base_nodes.txt");

    std::ifstream code_file(path.value());
    static std::string code; // TODO: this is shit!
    std::getline(code_file, code, '\0');

    return util::Parser::getWords(code);
}

#define NODE_MACROS(type_name, method, ...) \
    if (cur_type == #type_name)             \
    {                                       \
        a_web.populate##method(i[0], i);    \
    }

static void
populate(onto::Web& a_web) noexcept
{
    static auto settings = readDefaultNodes();

    std::string cur_type;
    for (auto& i : settings)
    {
        if (i[0] == "~")
        {
            cur_type = i[1];
            continue;
        }
        if (i.empty()) continue;

#include "./nodes/node.ini"
    }

    // onto::Web result;

    // result.populateType({"int", "float", "double", "bool", "char"});
    // result.populateOperator({"if", "for", "while"});

    // onto::Decoder::process(result, a_data);

    // result.clearNotUsedNodes();
    // return result;
}

static onto::Web
construct(const std::string& a_data) noexcept
{
    onto::Web result;

    // result.populateType({"int", "float", "double", "bool", "char"});
    // result.populateOperator({"if", "for", "while"});
    populate(result);

    onto::Decoder::process(result, a_data);

    result.clearNotUsedNodes();
    return result;
}

onto::Web
onto::WebFactory::fromFile(const std::string& a_filename) noexcept
{
    std::ifstream code_file(a_filename);
    std::string code;
    std::getline(code_file, code, '\0');
    return construct(code);
}

//--------------------------------------------------------------------------------
