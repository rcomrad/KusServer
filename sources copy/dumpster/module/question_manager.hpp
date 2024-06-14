#ifndef QUESTION_MANAGER_HPP
#define QUESTION_MANAGER_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "module_base.hpp"

//--------------------------------------------------------------------------------

namespace mod
{
class QuestionManager : public ModuleBase
{
protected:
    str::String doAction(const Command& aComman) noexcept override;

private:
    static QuestionManager mInstance;
    QuestionManager() noexcept;

    static str::String loadQuestions() noexcept;
    static str::String retestQuestions() noexcept;
};
} // namespace mod

//--------------------------------------------------------------------------------

#endif // !QUESTION_MANAGER_HPP
