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
    std::string doAction(const Command& aComman) noexcept override;

private:
    static QuestionManager mInstance;
    QuestionManager() noexcept;

    static std::string loadQuestions() noexcept;
    static std::string retestQuestions() noexcept;
};
} // namespace mod

//--------------------------------------------------------------------------------

#endif // !QUESTION_MANAGER_HPP
