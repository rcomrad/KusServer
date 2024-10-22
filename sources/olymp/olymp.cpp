#include "olymp.hpp"

#include "core/command/input_buffer.hpp"

#include "evaluate.hpp"

SINGLETON_DEFINITOR(olymp, Olymp)

olymp::Olymp::Olymp() noexcept : core::Module("olymp")
{
}

bool
olymp::Olymp::loopBody() noexcept
{
    // core::InputBuffer buffer;
    // auto cmd_out = buffer.execCommand("res_proc results.dmp");
    // printf("%s", cmd_out.get());

    return false;
}

void
olymp::Olymp::commandSetup() const noexcept
{
    registerCommand("res_proc", Evaluate::processResults,
                    "Process competition results.", "comp_res_file");
}

void
olymp::Olymp::variableSetup() const noexcept
{
    // registerVariable("token_status", serv::Token::VariableStrValues,
    //                  int(serv::Token::Status::MAX) - 1);
}
