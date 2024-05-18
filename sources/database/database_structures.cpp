#include "database_structures.hpp"

// std::string data::AnswerBase::tableName         = {"answer"};
// std::vector<data::Type> data::AnswerBase::types = {
//     data::Type::INT,    data::Type::INT,    data::Type::INT,
//     data::Type::STRING, data::Type::STRING, data::Type::FLOAT,
//     data::Type::STRING};
// std::vector<std::string> data::AnswerBase::columnNames = {
//     "id", "user_id", "question_id", "time", "verdict", "weight", "value"};
// std::unordered_map<std::string, uint8_t> data::AnswerBase::nameToNum = {
//     {"id",          0},
//     {"user_id",     1},
//     {"question_id", 2},
//     {"time",        3},
//     {"verdict",     4},
//     {"weight",      5},
//     {"value",       6}
// };

void
data::DummyBase::reset() noexcept
{
    a = 5;
    b = "abc";
    c = false;
    // c = 7.7;

    ptrs[0]  = (void*)(&a);
    ptrs[1]  = (void*)(&b);
    ptrs[2]  = (void*)(&c);
}

int
data::DummyBase::getCharCount() const noexcept
{
    return 9 + b.size() + 5 + 1;
}
