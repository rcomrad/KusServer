#include "decoder.hpp"

#include <functional>

#include "context_router.hpp"

void
onto::Decoder::process(Web& a_web, const std::string& a_data) noexcept
{
    Node* last_node_ptr = nullptr;
    std::string word;
    std::vector<Node*> node_stuck = {nullptr};
    std::vector<Context> context_stuck;

    static auto sep_null     = [&](char c) {};
    static auto sep_real     = [&](char c) { context_stuck.emplace_back(c); };
    static auto sep_collapse = [&](char c)
    {
        last_node_ptr = ContextRouter::process(ContextRouter::RouterInpData{
            a_web, node_stuck.back(), context_stuck});
        context_stuck.clear();
    };
    static auto sep_expand = [&](char c)
    {
        sep_collapse(c);
        node_stuck.emplace_back(last_node_ptr);
    };
    static auto sep_nerrow = [&](char c)
    {
        sep_collapse(c);
        node_stuck.pop_back();
    };

    bool need_pop_context = false;
    bool only_digits      = true;
    for (auto simbol : a_data)
    {
        bool word_complited                    = true;
        std::function<void(char)> sep_callback = sep_null;

        switch (simbol)
        {
            case ' ':
            case '\t':
                break;

            case '\n':
                if (context_stuck.empty() ||
                    context_stuck.front().type != Context::Type::PREPROCESSOR)
                {
                    break;
                }
            case ';':
            case '\0':
                sep_callback = sep_collapse;
                break;

            case '(':
            case ')':
            case ',':
            case '.':
            case '=':
            case '+':
            case '-':
            case '#':
            case '>':
            case '<':
                sep_callback = sep_real;
                break;

            case '{':
                sep_callback = sep_expand;
                break;

            case '}':
                sep_callback = sep_nerrow;
                break;

            default:
                if (!std::isdigit(simbol))
                {
                    only_digits = false;
                }

                word_complited = false;
                word.push_back(simbol);
                break;
        }

        if (word_complited)
        {
            if (!word.empty())
            {
                context_stuck.emplace_back(a_web.searchNode(word), word);
                word.clear();

                if (only_digits)
                {
                    context_stuck.back().type = Context::Type::NUMERICAL;
                }
            }
            only_digits = true;

            sep_callback(simbol);
            sep_callback = sep_null;
        }
    }
}

// bool
// foo(const std::string& a_reg_expr, const std::vector<Context>&
// a_context_stuck)
// {
//     int cur_cntx = 0;
//     for (int i = 0; i < a_reg_expr.size(); ++i)
//     {
//         auto
//         if (a_context_stuck[cur_cntx] )
//     }
// }

// onto::Node*
// onto::Decoder::collapse(std::vector<Context>& context_stuck,
//                         Node* a_parent_node) noexcept
// {
//     Node* result;

//     return result;
// }

// bool
// onto::Decoder::hasPattern(const std::vector<Context>& a_data,
//                           const std::vector<Type>& a_pattern) noexcept
// {
//     return false;
// }

// void
// onto::Decoder::processNonstatic(Web& a_web, const std::string& a_data)
// noexcept
// {
//     // int indx = 0;
//     std::string word;
//     // Command command;
//     // while (a_data[indx])
//     bool need_pop_context = false;
//     for (size_t indx = 0; a_data[indx]; ++indx)
//     {
//         switch (a_data[indx])
//         {
//             case ';':
//             case '}':
//             case '\0':
//                 need_pop_context = true;
//             case ' ':
//             case '\t':
//             case '\n':
//                 processWord(a_web, word);
//                 word.clear();
//                 break;
//             case '{':
//                 // expand
//                 break;
//             default:
//                 word += a_data[indx];
//                 break;
//         }

//         if (need_pop_context)
//         {
//             m_context_stuck.pop_back();
//             need_pop_context = false;
//         }
//     }
// }

// void
// onto::Decoder::processWord(Web& a_web, const std::string& a_word) noexcept
// {
//     auto node_opt = a_web.searchNode(a_word);
//     if (node_opt.has_value())
//     {
//         auto& node = node_opt.value();
//         switch (node.getKind())
//         {
//             case Node::Kind::TYPE:
//                 // a_command.m_type = dynamic_cast<Type&>(node);
//                 break;
//             case Node::Kind::OPERATOR:
//                 // a_command.m_operator = dynamic_cast<Operator&>(node);
//                 break;
//             default:
//                 break;
//         }
//         // m_context_stuck.emplace_back(state, &node);
//         m_context_stuck.emplace_back(&node);
//     }
//     else
//     {
//     }
// }
