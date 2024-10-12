#include "web_factory.hpp"

#include <fstream>

#include "decoder.hpp"

//--------------------------------------------------------------------------------

onto::Web
onto::WebFactory::fromFile(const std::string& a_filename) noexcept
{
    std::ifstream code_file(a_filename);
    std::string code;
    std::getline(code_file, code, '\0');
    return construct(code);
}

onto::Web
onto::WebFactory::construct(const std::string& a_data) noexcept
{
    Web result;

    result.populateType({"int", "float", "double", "bool", "char"});
    result.populateOperator({"if", "for", "while"});

    Decoder::process(result, a_data);

    result.clearNotUsedNodes();
    return result;
}

//--------------------------------------------------------------------------------
