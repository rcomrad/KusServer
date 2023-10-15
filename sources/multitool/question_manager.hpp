#ifndef QUESTION_MANAGER_HPP
#define QUESTION_MANAGER_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "core/module_base.hpp"

//--------------------------------------------------------------------------------

namespace mult
{
class QuestionManager : public core::ModuleBase
{
protected:
    std::string doAction() noexcept override;

private:
    static QuestionManager mInstance;
    QuestionManager() noexcept;

    static std::string loadQuestions() noexcept;
    static std::string retestQuestions() noexcept;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !QUESTION_MANAGER_HPP
