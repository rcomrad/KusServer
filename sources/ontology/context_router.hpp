#pragma once

#include <regex>
#include <vector>

#include "nodes/node.hpp"
#include "utility/common/holy_trinity.hpp"
#include "utility/datastructs/num_prefix_tree.hpp"

#include "context.hpp"
#include "web.hpp"

namespace onto
{

class ContextRouter
{
public:
    struct RouterInpData
    {
        Web& web;
        Node* parent_node;
        std::vector<Context>& context_stuck;
    };

    HOLY_TRINITY_SINGLETON(ContextRouter);
    SINGL_RET_METHOD(Node*, process, (const RouterInpData& a_data));

private:
    struct RegxObj
    {
        RegxObj(auto str, auto ptr) : regx(str), handler(ptr)
        {
        }
        decltype(std::regex("")) regx;
        Node* (*handler)(const RouterInpData&);
    };
    std::vector<RegxObj> m_router;

    ContextRouter();

    static Node* functionDeclaration(const RouterInpData& a_data);
    static Node* variableDeclaration(const RouterInpData& a_data);
    static Node* variable_expression(const RouterInpData& a_data);
    static Node* deleted(const RouterInpData& a_data);
    static Node* communication(const RouterInpData& a_data);
    static Node* preprocessor(const RouterInpData& a_data);
    static Node* basic(const RouterInpData& a_data);

    static Node* expression(const RouterInpData& a_data, int offset);
    static Node* cinCommunication(const RouterInpData& a_data);
    static Node* coutCommunication(const RouterInpData& a_data);
};

} // namespace onto
