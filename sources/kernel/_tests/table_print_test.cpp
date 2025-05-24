#include <algorithm>
#include <ranges>
#include <vector>

#include "kernel/framework/command/handler.hpp"
#include "kernel/framework/logger/include_me.hpp"
#include "kernel/tester/commands_fixture.hpp"

namespace kustest
{

struct Adress : public core::TablePrinter
{
    int building_numder;
    double x;
    double y;
    size_t coord_hash;
    std::string street_name;

    Adress(int a_building_numder,
           double a_x,
           double a_y,
           size_t a_coord_hash,
           const std::string& a_street_name)
        : building_numder(a_building_numder),
          x(a_x),
          y(a_y),
          coord_hash(a_coord_hash),
          street_name(a_street_name)
    {
    }

    void print() const override
    {
        building_info =
            addCell(building_numder).setName("building").alignmentRight();
        addCell(x).setName("x coord").alignmentRight();
        addCell(y).setName("y coord").alignmentMiddle();
        addCell(coord_hash).setName("hash").alignmentLeft();
        street_info = addCell(street_name).setName("street").alignmentLeft();
    }

    mutable int building_info;
    mutable int street_info;
};

template <typename T>
struct AdressList : public core::TablePrinter
{
    std::vector<T> adr_list;

    void print() const override
    {
        addTableConrainer(adr_list);
    }
};

class UTablePrinter : public Fixture
{
};

auto
getData()
{
    std::vector<Adress> adr_list;
    adr_list.emplace_back(32, 3.65, 567567.867, 453453, "Abasov streat");
    adr_list.emplace_back(35632, 0.675, 27, 65782345845, "Koyaanisquatsiuth");
    adr_list.emplace_back(12345, 78.3456, 0, 0, "Slavy");
    adr_list.emplace_back(0, 0, 3464.435, 2355, "Kafki");
    return adr_list;
}

TEST_F(UTablePrinter, simple)
{
    // clang-format off
    std::string answer =
        "| building |  x coord  |    y coord    |    hash     |      street       |\n"
        "|       32 |  3.650000 | 567567.867000 | 453453      | Abasov streat     |\n"
        "|    35632 |  0.675000 |   27.000000   | 65782345845 | Koyaanisquatsiuth |\n"
        "|    12345 | 78.345600 |   0.000000    | 0           | Slavy             |\n"
        "|        0 |  0.000000 |  3464.435000  | 2355        | Kafki             |\n";
    // clang-format on

    AdressList<Adress> list;
    list.adr_list = getData();
    auto result   = list.buildTable();

    ASSERT_NE(result.get(), nullptr);
    EXPECT_STREQ(answer.data(), result.get());

    result = list.buildTable();
    ASSERT_NE(result.get(), nullptr);
    EXPECT_STREQ(answer.data(), result.get());
}

struct AdditionalData
{
    int building_year;
    size_t street_hash;
    double normalized_hash;
};

struct IncreasedAdress : public Adress, public AdditionalData
{
    IncreasedAdress(const Adress& a_base_adres,
                    int a_building_year,
                    size_t a_street_hash,
                    double a_normalized_hash)
        : Adress(a_base_adres),
          AdditionalData(a_building_year, a_street_hash, a_normalized_hash)
    {
    }

    void print() const override
    {
        Adress::print();
        addSubline();
        addCell(building_info, building_year).alignmentMiddle();
        addCell(street_info, street_hash).alignmentLeft();
        addSubline();
        addCell(street_info, normalized_hash).alignmentRight();
    }
};

struct KeyedIncreasedAdress : public IncreasedAdress
{
    using IncreasedAdress::IncreasedAdress;

    void print() const override
    {
        IncreasedAdress::print();
        getKeyInfo();
    }
};

template <typename T>
auto
getComplexData()
{
    std::vector<AdditionalData> additional_data = {
        {1961,      3832116832,   7.6574  },
        {0,         4564,         1547    },
        {119611961, 975375375373, -0.99   },
        {-39,       10,           27.57667},
        {97978,     0,            596     },
    };
    std::reverse(additional_data.begin(), additional_data.end());

    std::vector<T> adr_list;
    for (auto& i : getData())
    {
        auto cur = additional_data.back();
        additional_data.pop_back();
        adr_list.emplace_back(i, cur.building_year, cur.street_hash,
                              cur.normalized_hash);
    }
    return adr_list;
}

TEST_F(UTablePrinter, subline)
{
    // clang-format off
    std::string answer =
        "| building  |  x coord  |    y coord    |    hash     |      street       |\n"
        "|        32 |  3.650000 | 567567.867000 | 453453      | Abasov streat     |\n"
        "|   1961    |           |               |             | 3832116832        |\n"
        "|           |           |               |             |          7.657400 |\n"
        "|     35632 |  0.675000 |   27.000000   | 65782345845 | Koyaanisquatsiuth |\n"
        "|     0     |           |               |             | 4564              |\n"
        "|           |           |               |             |       1547.000000 |\n"
        "|     12345 | 78.345600 |   0.000000    | 0           | Slavy             |\n"
        "| 119611961 |           |               |             | 975375375373      |\n"
        "|           |           |               |             |         -0.990000 |\n"
        "|         0 |  0.000000 |  3464.435000  | 2355        | Kafki             |\n"
        "|    -39    |           |               |             | 10                |\n"
        "|           |           |               |             |         27.576670 |\n";
    // clang-format on

    AdressList<IncreasedAdress> list;
    list.adr_list = getComplexData<IncreasedAdress>();
    auto result   = list.buildTable();

    ASSERT_NE(result.get(), nullptr);
    EXPECT_STREQ(answer.data(), result.get());

    result = list.buildTable();
    ASSERT_NE(result.get(), nullptr);
    EXPECT_STREQ(answer.data(), result.get());
}

TEST_F(UTablePrinter, keyed_subline)
{
    // clang-format off
    std::string answer =
        "| # | building  |  x coord  |    y coord    |    hash     |      street       |\n"
        "| 0 |        32 |  3.650000 | 567567.867000 | 453453      | Abasov streat     |\n"
        "|   |   1961    |           |               |             | 3832116832        |\n"
        "|   |           |           |               |             |          7.657400 |\n"
        "| 1 |     35632 |  0.675000 |   27.000000   | 65782345845 | Koyaanisquatsiuth |\n"
        "|   |     0     |           |               |             | 4564              |\n"
        "|   |           |           |               |             |       1547.000000 |\n"
        "| 2 |     12345 | 78.345600 |   0.000000    | 0           | Slavy             |\n"
        "|   | 119611961 |           |               |             | 975375375373      |\n"
        "|   |           |           |               |             |         -0.990000 |\n"
        "| 3 |         0 |  0.000000 |  3464.435000  | 2355        | Kafki             |\n"
        "|   |    -39    |           |               |             | 10                |\n"
        "|   |           |           |               |             |         27.576670 |\n";
    // clang-format on

    AdressList<KeyedIncreasedAdress> list;
    list.adr_list = getComplexData<KeyedIncreasedAdress>();
    auto result   = list.buildTable();

    ASSERT_NE(result.get(), nullptr);
    EXPECT_STREQ(answer.data(), result.get());

    result = list.buildTable();
    ASSERT_NE(result.get(), nullptr);
    EXPECT_STREQ(answer.data(), result.get());
}

struct ComplexData : public Adress
{
    ComplexData() = default;

    ComplexData(const Adress& a_base, const KeyedIncreasedAdress& a_dereved)
        : Adress(a_base), second_table(a_dereved)
    {
    }
    KeyedIncreasedAdress second_table;

    void print() const override
    {
        Adress::print();
        addCell(second_table);
    }
};

struct CombinedTable : public core::TablePrinter
{
public:
    CombinedTable()
    {
        auto simpl_list = getData();
        std::ranges::reverse(simpl_list);
        auto complex_list = getComplexData<KeyedIncreasedAdress>();

        for (int i = 0; i < std::min(simpl_list.size(), complex_list.size());
             ++i)
        {
            m_data.emplace_back(simpl_list.at(i), complex_list.at(i));
        }
    }

    void print() const override
    {
        addTableConrainer(m_data);
    }

private:
    std::vector<ComplexData> m_data;
};

TEST_F(UTablePrinter, complex_table)
{
    // clang-format off
    std::string answer =
        "| # | building |  x coord  |    y coord    |    hash     |      street       | building  |  x coord  |    y coord    |    hash     |      street       |\n"
        "| 0 |        0 |  0.000000 |  3464.435000  | 2355        | Kafki             |        32 |  3.650000 | 567567.867000 | 453453      | Abasov streat     |\n"
        "|   |          |           |               |             |                   |   1961    |           |               |             | 3832116832        |\n"
        "|   |          |           |               |             |                   |           |           |               |             |          7.657400 |\n"
        "| 1 |    12345 | 78.345600 |   0.000000    | 0           | Slavy             |     35632 |  0.675000 |   27.000000   | 65782345845 | Koyaanisquatsiuth |\n"
        "|   |          |           |               |             |                   |     0     |           |               |             | 4564              |\n"
        "|   |          |           |               |             |                   |           |           |               |             |       1547.000000 |\n"
        "| 2 |    35632 |  0.675000 |   27.000000   | 65782345845 | Koyaanisquatsiuth |     12345 | 78.345600 |   0.000000    | 0           | Slavy             |\n"
        "|   |          |           |               |             |                   | 119611961 |           |               |             | 975375375373      |\n"
        "|   |          |           |               |             |                   |           |           |               |             |         -0.990000 |\n"
        "| 3 |       32 |  3.650000 | 567567.867000 | 453453      | Abasov streat     |         0 |  0.000000 |  3464.435000  | 2355        | Kafki             |\n"
        "|   |          |           |               |             |                   |    -39    |           |               |             | 10                |\n"
        "|   |          |           |               |             |                   |           |           |               |             |         27.576670 |\n";
    // clang-format on

    CombinedTable table;
    auto result = table.buildTable();

    ASSERT_NE(result.get(), nullptr);
    EXPECT_STREQ(answer.data(), result.get());

    result = table.buildTable();
    ASSERT_NE(result.get(), nullptr);
    EXPECT_STREQ(answer.data(), result.get());
}

class TestCommandHandler : public core::CommandHandler
{
public:
    auto buildTable()
    {
        return core::CommandHandler::buildTable();
    }
};

TEST_F(UTablePrinter, command_handler_help)
{
    // clang-format off
    std::string answer =
        "      help | Args: /* no args */                                                                                                                     \n"
        "           | Displays a list of all available commands.                                                                                              \n"
        "           |                                                                                                                                         \n"
        "  var_help | Args: [variable_name]...                                                                                                                \n"
        "           | Print the possible values of the variables. If the variable names are not specified, print all the variable and their possible values.  \n"
        "           |                                                                                                                                         \n"
        "   var_set | Args: variable_name=variable_value...                                                                                                   \n"
        "           | Assign a value to the specified variable.                                                                                               \n"
        "           |                                                                                                                                         \n"
        "  var_show | Args: [variable_name]...                                                                                                                \n"
        "           | Print the current value for the specified variable. If no name is specified, all variables will be selected.                            \n"
        "           |                                                                                                                                         \n";
    // clang-format on

    TestCommandHandler handler;
    handler.registrateCommand(
        0, "___internal_test", nullptr,
        "This command is used in unit tests. Don't use it. It's meaningless.",
        "");
    handler.registrateCommand(0, "help", nullptr,
                              "Displays a list of all available commands.", "");
    handler.registrateCommand(0, "var_set", nullptr,
                              "Assign a value to the specified variable.",
                              "variable_name=variable_value...");
    handler.registrateCommand(
        0, "var_show", nullptr,
        "Print the current value for the specified variable. If no "
        "name is specified, all variables will be selected.",
        "[variable_name]...");
    handler.registrateCommand(
        0, "var_help", nullptr,
        "Print the possible values of the variables. "
        "If the variable names are not specified, "
        "print all the variable and their possible values.",
        "[variable_name]...");

    auto result = handler.buildTable();

    ASSERT_NE(result.get(), nullptr);
    EXPECT_STREQ(answer.data(), result.get());

    result = handler.buildTable();
    ASSERT_NE(result.get(), nullptr);
    EXPECT_STREQ(answer.data(), result.get());
}

struct SimpleArray : public core::TablePrinter
{
    std::vector<int> m_data = {5, -3, 4, -3, 0, 6, 9, 0};

    void print() const override
    {
        setDefaultSeparator(' ');
        getKeyInfo();
        addTableConrainer(m_data);
    }
};

TEST_F(UTablePrinter, simple_array)
{
    // clang-format off
    std::string answer =
        "  #  \n"
        "  0  \n"
        "  1  \n"
        "  2  \n"
        "  3  \n"
        "  4  \n"
        "  5  \n"
        "  6  \n"
        "  7  \n";
    // clang-format on

    SimpleArray array;
    auto result = array.buildTable();

    ASSERT_NE(result.get(), nullptr);
    EXPECT_STREQ(answer.data(), result.get());

    result = array.buildTable();
    ASSERT_NE(result.get(), nullptr);
    EXPECT_STREQ(answer.data(), result.get());
}

} // namespace kustest
