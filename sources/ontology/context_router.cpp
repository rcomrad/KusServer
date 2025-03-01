#include "context_router.hpp"

#include <iostream>

onto::ContextRouter::ContextRouter()
{
    // TODO: ^ - begining of the string $ - end of sting
    //  m_cntx_router.set({Context::Type::NONE}, ContextRouter::basic);
    //  m_router["[a-z]"] = ContextRouter::basic;
    m_router.emplace_back(".*d.*", &ContextRouter::deleted);
    m_router.emplace_back("^p.*", &ContextRouter::preprocessor);
    m_router.emplace_back("tw\\(\\)", &ContextRouter::functionDeclaration);
    m_router.emplace_back("t(w|w=[w,n,v])(,(w|w=[w,n,v]))*",
                          &ContextRouter::variableDeclaration);
    m_router.emplace_back("^v=[w,n,v,m]*", &ContextRouter::variable_expression);
    m_router.emplace_back("c.*", &ContextRouter::communication);
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

    if (a_data.context_stuck.empty()) return nullptr;

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
    Node* result = nullptr;
    std::cout << "basic" << std::endl;
    throw std::runtime_error("No handler specified!");
    return result;
}

onto::Node*
onto::ContextRouter::deleted(const RouterInpData& a_data)
{
    Node* result = nullptr;
    std::cout << "deleted" << std::endl;
    return result;
}

onto::Node*
onto::ContextRouter::preprocessor(const RouterInpData& a_data)
{
    Node* result = nullptr;
    std::cout << "preprocessor" << std::endl;
    return result;
}

onto::Node*
onto::ContextRouter::cinCommunication(const RouterInpData& a_data)
{
    Node* result = nullptr;
    std::cout << "cin" << std::endl;

    auto& stuck = a_data.context_stuck;
    auto& comm  = *dynamic_cast<Communication*>(stuck[0].ptr);
    for (int i = 2; i < stuck.size(); ++i)
    {
        if (stuck[i].type == Context::Type::ANGLE_BRA) continue;

        if (stuck[i].type != Context::Type::VARIABLE)
            throw std::runtime_error("Wrong user data!");

        auto& var  = *dynamic_cast<Variable*>(stuck[i].ptr);
        auto& data = a_data.web.createUserData(comm);
        var.setValue(data);
    }
    return result;
}

onto::Node*
onto::ContextRouter::coutCommunication(const RouterInpData& a_data)
{
    Node* result = nullptr;
    std::cout << "cout" << std::endl;

    auto& stuck = a_data.context_stuck;
    auto& comm  = *dynamic_cast<Communication*>(stuck[0].ptr);
    for (int l = 1; l < stuck.size(); ++l)
    {
        while (l < stuck.size() && stuck[l].type == Context::Type::ANGLE_BRA)
            ++l;
        int r = l + 1;
        while (r < stuck.size() && stuck[r].type != Context::Type::ANGLE_BRA)
            ++r;

        Node* out_data = stuck[r + 1].ptr;
        if (r - l > 1)
        {
            RouterInpData data = a_data;
            data.web           = a_data.web;
            data.context_stuck =
                std::vector<Context>(stuck.begin() + l, stuck.begin() + r);
            out_data = expression(data, 0);
        }

        auto& data = a_data.web.createUserData(comm);
        data.output(*out_data);

        l = r;
    }
    return result;
}

onto::Node*
onto::ContextRouter::communication(const RouterInpData& a_data)
{
    Node* result = nullptr;
    std::cout << "communication" << std::endl;

    if (a_data.context_stuck[0].ptr->getName() == "cin")
        cinCommunication(a_data);
    if (a_data.context_stuck[0].ptr->getName() == "cout")
        coutCommunication(a_data);

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
            auto expr = variable_expression(expr_data);
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
    auto& literal = web.createLiteral("lit_" + cur_cntx.word);
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
onto::ContextRouter::expression(const RouterInpData& a_data, int offset)
{
    std::cout << "expression" << std::endl;

    auto& stuck = a_data.context_stuck;
    int indx    = offset;
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
            case Context::Type::PLUS:
            case Context::Type::MINUS:
                part_data.recordCntxWord(stuck[indx]);
                break;

            default:
                throw std::runtime_error(
                    "Unexpected expression parts type with id '" +
                    std::to_string(int(stuck[indx].type)) + "'");
                break;
        }
    }

    auto& result = a_data.web.createExpression(part_data.name, part_data.parts);

    return &result;
}

onto::Node*
onto::ContextRouter::variable_expression(const RouterInpData& a_data)
{
    std::cout << "variable_expression" << std::endl;

    auto& var_node = *dynamic_cast<Variable*>(a_data.context_stuck[0].ptr);
    auto expr      = static_cast<Expression*>(expression(a_data, 2));
    var_node.setValue(*expr);
    return expr;
}

// // Matches one or more digits
// std::string pattern_text = "\\d+";
// std::cout << "digits (" << pattern_text << "):\n";
// auto pattern = std::regex(pattern_text);
// match_and_print(text, pattern);
