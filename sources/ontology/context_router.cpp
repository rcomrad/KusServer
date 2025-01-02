#include "context_router.hpp"

#include <iostream>

onto::ContextRouter::ContextRouter()
{
    // TODO: ^ - begining of the string $ - end of sting
    //  m_cntx_router.set({Context::Type::NONE}, ContextRouter::basic);
    //  m_router["[a-z]"] = ContextRouter::basic;
    m_router.emplace_back("tw\\(\\)", &ContextRouter::functionDeclaration);
    m_router.emplace_back("t(w|w=[w,n,v])(,(w|w=[w,n,v]))*",
                          &ContextRouter::variableDeclaration);
    m_router.emplace_back("v=[w,n,v]", &ContextRouter::expression);
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
            // TODO: ranges?
            std::vector<Context> substuck(a_data.context_stuck.begin() + i,
                                          a_data.context_stuck.begin() + i + 3);
            substuck.front().ptr  = &result;
            substuck.front().type = Context::Type::VARIABLE;
            RouterInpData expr_data(a_data.web, a_data.parent_node, substuck);
            auto expr = expression(expr_data);
            i += 2;
        }
        if (stuck[i + 1].type == Context::Type::DEVIDE)
        {
            i += 1;
        }
    }

    return nullptr;
}

struct PartData
{
    onto::Web& web;
    int& indx;
    std::vector<onto::Context>& stuck;

    std::string name;
    std::vector<onto::Node*> parts;

    void recordCntxWord(onto::Context& a_cntx)
    {
        name += a_cntx.word;
        name.push_back(' ');
    }

    void recordCntxWord()
    {
        recordCntxWord(stuck[indx]);
    }
};

#define PART_DATA_EXPAND                              \
    onto::Web& web                    = a_data.web;   \
    int& indx                         = a_data.indx;  \
    std::vector<onto::Context>& stuck = a_data.stuck; \
    std::string& name                 = a_data.name;  \
    std::vector<onto::Node*>& parts   = a_data.parts; \
    onto::Context& cur_cntx           = stuck[indx];

static void
add_expr_part_number(PartData& a_data)
{
    PART_DATA_EXPAND;
    auto& literal = web.createLiteral(cur_cntx.word);
    a_data.recordCntxWord();
    parts.emplace_back(&literal);
}

static void
add_expr_part_var(PartData& a_data)
{
    PART_DATA_EXPAND;
    parts.emplace_back(cur_cntx.ptr);
    a_data.recordCntxWord();
}

#undef PART_DATA_EXPAND

onto::Node*
onto::ContextRouter::expression(const RouterInpData& a_data)
{
    std::cout << "expression" << std::endl;

    auto& var_node = *dynamic_cast<Variable*>(a_data.context_stuck[0].ptr);

    auto& stuck = a_data.context_stuck;
    int indx    = 2;
    PartData part_data(a_data.web, indx, stuck);

    for (; indx < stuck.size(); ++indx)
    {
        switch (stuck[indx].type)
        {
            case Context::Type::NUMERICAL:
                add_expr_part_number(part_data);
                break;

            case Context::Type::VARIABLE:
                add_expr_part_var(part_data);
                break;

            case Context::Type::OPERATOR:
                break;

            default:
                throw std::runtime_error(
                    "Unexpected expression parts type with id '" +
                    std::to_string(int(stuck[indx].type)) + "'");
                break;
        }
    }

    auto& result = a_data.web.createExpression(part_data.name, part_data.parts);
    result.addNeighbor(var_node, Relation::LOCATED_IN);

    return &result;
}

// // Matches one or more digits
// std::string pattern_text = "\\d+";
// std::cout << "digits (" << pattern_text << "):\n";
// auto pattern = std::regex(pattern_text);
// match_and_print(text, pattern);
