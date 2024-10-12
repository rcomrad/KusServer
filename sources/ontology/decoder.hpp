#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include "context.hpp"
#include "web.hpp"

namespace onto
{

class Decoder
{
public:
    Decoder() = delete;

    static void process(Web& a_web, const std::string& a_data) noexcept;

private:
    // static Node* collapse(std::vector<Context>& context_stuck,
    //                       Node* a_parent_node) noexcept;

    // bool hasPattern(const std::vector<Context>& a_data,
    //                 const std::vector<Type>& a_pattern) noexcept;

    // struct Context
    // {
    //     enum State
    //     {
    //         NUN,
    //         EMPTY,
    //         TYPE,
    //         MAX
    //     };
    //     Node* node;
    //     State state;
    // };
    // std::vector<Context> m_context_stuck;

    // void process(const std::string& a_str) noexcept;
    // static void processNonstatic(Web& a_web,
    //                              const std::string& a_data) noexcept;

    // static void processWord(Web& a_web, const std::string& a_word) noexcept;
};

} // namespace onto
