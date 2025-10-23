#pragma once

#include <boost/preprocessor.hpp>

#include <string>

#include "kernel/utility/string/slicer.hpp"

#include "mass_executor.hpp"
#include "table_base.hpp"

// Определяем поля как последовательность
// CREATE_STRUCT(Person, ((int, id))((std::string, login))((std::string,
// password))((std::string, last_login)))

#define GET_TYPE(elem) BOOST_PP_TUPLE_ELEM(2, 0, elem)
#define GET_NAME(elem) BOOST_PP_TUPLE_ELEM(2, 1, elem)

// Генерация полей структуры: type name;
#define FIELD_DECL(r, data, elem) GET_TYPE(elem) GET_NAME(elem);

// Генерация конструктора
#define FIELD_CONSTR_ARGS(r, data, elem) \
    GET_TYPE(elem) BOOST_PP_CAT(a_, GET_NAME(elem)),
#define FIELD_CONSTR_INIT(r, data, elem) \
    GET_NAME(elem)(BOOST_PP_CAT(a_, GET_NAME(elem))),

// Помощник для select с индексом
#define FIELD_SELECT(r, a_psql, i, elem) \
    GET_NAME(elem) = a_psql.get<GET_TYPE(elem)>(i + 1);

#define FIELD_INSERT(r, data, elem) \
    a_sb.addDBData(GET_NAME(elem)); \
    a_sb.add(',');

#define FIELD_DUMP(r, data, elem) result += dumpType(GET_NAME(elem));

#define FIELD_UPDATE(r, data, elem)               \
    a_sb.add(BOOST_PP_STRINGIZE(GET_NAME(elem))); \
    a_sb.add('=');                                \
    a_sb.addDBData(GET_NAME(elem));               \
    a_sb.add(',');

#define FIELD_INFO(r, data, elem) \
    addInfo(result, BOOST_PP_STRINGIZE(GET_NAME(elem)), GET_TYPE(elem){});

#define FIELD_LOAD(r, data, i, elem) loadType(parts[i + 1], GET_NAME(elem));

#define FIELD_EQ(r, data, elem) \
    result &= GET_NAME(elem) == a_other.GET_NAME(elem);

// Макрос для генерации структуры целиком
#define CREATE_STRUCT(name, fields_seq)                                  \
    struct name : public database::TableBase                             \
    {                                                                    \
        BOOST_PP_SEQ_FOR_EACH(FIELD_DECL, _, fields_seq)                 \
                                                                         \
        name() = default;                                                \
        name(int a_id,                                                   \
             BOOST_PP_SEQ_FOR_EACH(FIELD_CONSTR_ARGS,                    \
                                   _,                                    \
                                   fields_seq) int dummy = 0)            \
            : BOOST_PP_SEQ_FOR_EACH(FIELD_CONSTR_INIT, _, fields_seq)    \
                  TableBase(a_id)                                        \
        {                                                                \
        }                                                                \
                                                                         \
        name(std::string_view a_data)                                    \
        {                                                                \
            auto parts = util::Slicer::copy(a_data, ";");                \
            BOOST_PP_SEQ_FOR_EACH_I(FIELD_LOAD, _, fields_seq)           \
        }                                                                \
                                                                         \
        bool operator==(const name& a_other) const                       \
        {                                                                \
            bool result = id == a_other.id;                              \
            BOOST_PP_SEQ_FOR_EACH(FIELD_EQ, _, fields_seq)               \
            return result;                                               \
        }                                                                \
                                                                         \
        void select(database::PostgreSQL& a_psql)                        \
        {                                                                \
            selectBase(a_psql);                                          \
            BOOST_PP_SEQ_FOR_EACH_I(FIELD_SELECT, a_psql, fields_seq)    \
        }                                                                \
                                                                         \
        void insert(util::StringBuilder& a_sb) const                     \
        {                                                                \
            insertBase(a_sb);                                            \
            BOOST_PP_SEQ_FOR_EACH(FIELD_INSERT, _, fields_seq)           \
            a_sb.pop_back();                                             \
        }                                                                \
                                                                         \
        std::string dump() const                                         \
        {                                                                \
            std::string result;                                          \
            result += dumpType(id);                                      \
            BOOST_PP_SEQ_FOR_EACH(FIELD_DUMP, _, fields_seq)             \
            return result;                                               \
        }                                                                \
                                                                         \
        void update(util::StringBuilder& a_sb) const                     \
        {                                                                \
            BOOST_PP_SEQ_FOR_EACH(FIELD_UPDATE, _, fields_seq);          \
            a_sb.pop_back();                                             \
        }                                                                \
                                                                         \
        static std::string_view getTableName()                           \
        {                                                                \
            return #name;                                                \
        }                                                                \
                                                                         \
        static std::string getTableInfo()                                \
        {                                                                \
            std::string result;                                          \
            BOOST_PP_SEQ_FOR_EACH(FIELD_INFO, _, fields_seq)             \
            result.pop_back();                                           \
            return result;                                               \
        }                                                                \
                                                                         \
    private:                                                             \
        static inline database::MassExecutor::Registrator<name> g_dummy; \
    };

// #define CREATE_STRUCT(name, fields_seq)                               \
//     struct name                                                       \
//     {                                                                 \
//         BOOST_PP_SEQ_FOR_EACH(FIELD_DECL, _, fields_seq)              \
//         void select(database::PostgreSQL& a_psql)                     \
//         {                                                             \
//             int index = 0;                                            \
//             BOOST_PP_SEQ_FOR_EACH_I(FIELD_SELECT, a_psql, fields_seq) \
//         }                                                             \
//     };

/*

#include <boost/preprocessor.hpp>
#include <string>

// Определяем поля как последовательность
// CREATE_STRUCT(Person, ((int, id))((std::string, login))((std::string,
password))((std::string, last_login)))

#define GET_TYPE(elem) BOOST_PP_TUPLE_ELEM(2, 0, elem)
#define GET_NAME(elem) BOOST_PP_TUPLE_ELEM(2, 1, elem)

// Генерация полей структуры: type name;
#define FIELD_DECL(r, data, elem) GET_TYPE(elem) GET_NAME(elem);

// Генерация строк присваивания в select
#define FIELD_SELECT_ASSIGN(r, data, elem) \
    GET_NAME(elem) = a_req.get<GET_TYPE(elem)>(data);

// Генерация добавления поля в insert
#define FIELD_INSERT_APPEND(r, data, elem) \
    data += std::to_string(GET_NAME(elem)) + ",";  // это подходит только
для чисел!

// Для std::string нужен особый случай, сделаем обертку для std::string
(покажу ниже)

// Промежуточный макрос для вставки в insert с учётом типа
#define FIELD_INSERT_APPEND2(r, data, elem) \
    field_insert_impl(data, GET_NAME(elem));


// Специализация функции вставки в строку для разных типов
inline void field_insert_impl(std::string& str, const int& value)
{
    str += std::to_string(value) + ",";
}

inline void field_insert_impl(std::string& str, const std::string& value)
{
    str += value + ",";
}

// ... добавляй другие перегрузки при необходимости

// Макрос для генерации структуры целиком
#define CREATE_STRUCT(name, fields_seq) \
struct name \
{ \
    BOOST_PP_SEQ_FOR_EACH(FIELD_DECL, _, fields_seq) \
\
    void select(req& a_req) \
    { \
        int index = 0; \
        BOOST_PP_SEQ_FOR_EACH_I(SELECT_ASSIGN_IMPL, a_req, fields_seq) \
    } \
\
    void insert(std::string& str) \
    { \
        BOOST_PP_SEQ_FOR_EACH(FIELD_INSERT_APPEND2, str, fields_seq) \
    } \
\
    std::string getTableName() \
    { \
        return BOOST_PP_STRINGIZE(name); \
    } \
}; \

// Помощник для select с индексом
#define SELECT_ASSIGN_IMPL(r, a_req, i, elem) \
    GET_NAME(elem) = a_req.get<GET_TYPE(elem)>(i);






// Определяем структуру
CREATE_STRUCT(Person,
    ((int, id))
    ((std::string, login))
    ((std::string, password))
    ((std::string, last_login))
)

// Пример вызова
req r;
Person u;
u.select(r);
std::string s;
u.insert(s);


*/
