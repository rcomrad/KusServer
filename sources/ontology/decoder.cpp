#include "decoder.hpp"

#include "command.hpp"

std::string
onto::Decoder::process(Web& a_web, const std::string& a_data) noexcept
{
    int indx = 0;
    std::string word;
    Command command;
    while (a_data[indx])
    {
        switch (a_data[indx])
        {
            case ' ':
            case '\t':
            case '\n':
            case ';':
            case '{':
            case '}':
                processWord(a_web, command, word);
                break;
            case '\0':
                break;
            default:
                word += a_data[indx];
                break;
        }
    }

    return "";
}

void
onto::Decoder::processWord(Web& a_web,
                           Command& a_command,
                           const std::string& a_word) noexcept
{
    auto node_opt = a_web.get_node(a_word);
    if (node_opt.has_value())
    {
        auto& node = node_opt.value();
        switch (node.getKind())
        {
            case Node::Kind::TYPE:
                a_command.m_type = dynamic_cast<Type&>(node);
                break;
            case Node::Kind::OPERATOR:
                a_command.m_operator = dynamic_cast<Operator&>(node);
                break;
            default:
                break;
        }
    }
}
