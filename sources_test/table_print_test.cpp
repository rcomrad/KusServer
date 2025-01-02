#include <vector>

#include "core/logging/table_printer.hpp"
#include "core/logging/table_storage.hpp"

#include "fixture.hpp"

namespace kustest
{

// #define SHORT_RND       std::rand() / 1024 - RAND_MAX / 2 / 1024
// #define LONG_RND        std::rand() - RAND_MAX
// #define FLOAT_RND       (SHORT_RND) / 1000
// #define DOUBLE_RND      (LONG_RND) / 1000
// #define ARRAG_RND(name) name[std::rand() % name.size()]

static std::vector<int> ints_array       = {0,  2,   234, 5,       24,   -234,
                                            -3, -46, -9,  2153253, -3432};
static std::vector<double> doubles_array = {
    0.12,  -0.4, -0.45345, -345.3453, -45.1,     -8.8,       -0.99,
    76.76, 5.23, 5.54,     5.76,      -999.8678, 43543.43453

};

static std::vector<const char*> street_names_array = {
    "Kuna",  "Slavy",      "Pobedy",      "Razmarina",      "Kafki",
    "Daddy", "Pskovskaya", "Moskovskaya", "Rozy Luksemburg"};
static std::vector<const char*> names_array = {
    "Alex", "Slava", "Tyoma", "Bob", "Jhon", "Cena", "Lev", "Misha", "Ksy"};
static std::vector<const char*> surnames_array = {
    "Orestovich", "Frolov",  "Bezdelnyi",        "Letyaga",
    "Orestovich", "Frolov",  "Bezdelnyi",        "Letyaga",
    "Varvarov",   "Kusakin", "Koyaanisquatsiuth"};

#define ARRAG_RND(name) name[std::rand() % name.size()]

struct Adress
{
    int building_numder;
    double x;
    double y;
    uint64_t coord_hash;
    std::string street_name;
    // const char* street_name;
    // const char* -> *(const char**)(a_data_ptr + 32)

    Adress() noexcept
        : building_numder(ARRAG_RND(ints_array)),
          x(ARRAG_RND(doubles_array)),
          y(ARRAG_RND(doubles_array)),
          coord_hash(ARRAG_RND(ints_array)),
          street_name(ARRAG_RND(street_names_array))
    {
    }

private:
    TABLE_REGISTER_HPP(
        Adress,
        .addCol(obj.building_numder, obj.x, obj.y, obj.street_name))

    // Expands to:
    // struct AdressTABLE_REGISTER
    // {
    //     inline AdressTABLE_REGISTER() noexcept
    //     {
    //         Adress* obj_ptr = nullptr;
    //         Adress& obj     = *obj_ptr;
    //         core::TableInfo info(obj);
    //         info.addCol(obj.building_numder, obj.x, obj.y, obj.street_name);
    //         core::TableStorage::addTableInfo(std::type_index(typeid(obj)),
    //                                          info);
    //     }
    // };
    // static AdressTABLE_REGISTER AdressTABLE_REGISTERglobal;
};

TABLE_REGISTER_CPP(kustest, Adress);

struct Person
{
    Adress adress;
    int id;
    char name[50];
    std::string surname;
    uint64_t name_hash;
    float weight;
    float high;
    uint64_t body_hash;

    Person() noexcept
        : id(ARRAG_RND(ints_array)),
          surname(ARRAG_RND(surnames_array)),
          name_hash(ARRAG_RND(ints_array)),
          weight(ARRAG_RND(doubles_array)),
          high(ARRAG_RND(doubles_array)),
          body_hash(ARRAG_RND(ints_array))
    {
        auto ptr = ARRAG_RND(names_array);
        strcpy(name, ptr);
    }

private:
    TABLE_REGISTER_HPP(
        Person,
        .addCol(obj.id, obj.name, obj.surname, obj.weight, obj.high)
            .addRow(obj.adress))
};

TABLE_REGISTER_CPP(kustest, Person);

struct Journal
{
    std::vector<Person> data;
};

class UTestTablePrint : public Fixture
{
};

TEST_F(UTestTablePrint, simpl_print)
{
    std::srand(1264970717);
    Journal j;

    // TODO: turn on test
    // for (int i = 0; i < 15; ++i)
    // {
    //     j.data.emplace_back();
    //     std::cout << core::TablePrinter::print(
    //                      j.data, {"id", "name", "surname", "weight", "high",
    //                               "building_numder", "x", "y",
    //                               "street_name"})
    //               << std::endl;
    // }
}

} // namespace kustest
