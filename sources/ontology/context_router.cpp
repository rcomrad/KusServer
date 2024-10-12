#include "context_router.hpp"

#include <iostream>

onto::ContextRouter::ContextRouter()
{
    // TODO: ^ - begining of the string $ - end of sting
    //  m_cntx_router.set({Context::Type::NONE}, ContextRouter::basic);
    //  m_router["[a-z]"] = ContextRouter::basic;
    m_router.emplace_back("tw\\(\\)", &ContextRouter::functionDeclaration);
    m_router.emplace_back("t(w|w=w)(,(w|w=w))*",
                          &ContextRouter::variableDeclaration);
    m_router.emplace_back(".*", &ContextRouter::basic);
}

onto::Node*
onto::ContextRouter::processNonstatic(const RouterInpData& a_data) noexcept
{
    // auto handler = m_cntx_router.get(a_context_stuck);
    // if (handler)
    // {
    //     handler.value()(a_web, a_parent_node, a_context_stuck);
    // }

    std::string cntx;
    for (const auto& i : a_data.context_stuck)
    {
        cntx.push_back(i);
    }
    std::cout << cntx << std::endl;

    Node* result = nullptr;
    for (const auto& i : m_router)
    {
        // if (std::regex_search(cntx, i.regx))
        if (std::regex_match(cntx, i.regx))
        {
            result = i.handler(a_data);
            break;
        }
    }
    return result;
}

onto::Node*
onto::ContextRouter::basic(const RouterInpData& a_data)
{
    Node* result;
    std::cout << "basic" << std::endl;
    return result;
}

onto::Node*
onto::ContextRouter::functionDeclaration(const RouterInpData& a_data)
{
    std::cout << "function_declaration" << std::endl;

    auto& type_node = *dynamic_cast<Type*>(a_data.context_stuck[0].ptr);
    auto& func_name = a_data.context_stuck[1].word;

    auto& result = a_data.web.createFunction(func_name, type_node);
    return &result;
}

onto::Node*
onto::ContextRouter::variableDeclaration(const RouterInpData& a_data)
{
    std::cout << "variable_declaration" << std::endl;

    auto& type_node = *dynamic_cast<Type*>(a_data.context_stuck[0].ptr);

    auto& stuck = a_data.context_stuck;
    for (int i = 1; i < stuck.size(); ++i)
    {
        auto& cntx = stuck[i];
        // TODO: =

        auto& result = a_data.web.createVariable(cntx.word, type_node);
        if (i + 1 >= stuck.size()) continue;

        if (stuck[i + 1].type == Context::Type::ASSIGN)
        {
            i += 2;
        }
        if (stuck[i + 1].type == Context::Type::DEVIDE)
        {
            i += 1;
        }
    }

    return nullptr;
}

// // Matches one or more digits
// std::string pattern_text = "\\d+";
// std::cout << "digits (" << pattern_text << "):\n";
// auto pattern = std::regex(pattern_text);
// match_and_print(text, pattern);
