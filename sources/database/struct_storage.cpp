#include "struct_storage.hpp"

#include <cstring>
#include <string>

#include "utility/string/slicer.hpp"

data::StructStorage&
data::StructStorage::getInstance() noexcept
{
    static StructStorage instance;
    return instance;
}

//--------------------------------------------------------------------------------

data::struct_id_t
data::StructStorage::registrateStruct(const char* a_struct_name,
                                      const char* a_struct_vars) noexcept
{
    return getInstance().registrateStructNonstatic(a_struct_name,
                                                   a_struct_vars);
}

data::struct_id_t
data::StructStorage::registrateStructNonstatic(
    const char* a_struct_name,
    const char* a_struct_vars) noexcept
{
    auto& data = m_struct_data.emplace_back();
    // TODO: make safe
    strcpy(data.name, a_struct_name);
    data.str_max_size = 0;

    uint8_t cnt = 0;
    static_assert(sizeof(cnt) == sizeof(data.count));

    // TODO: remove if-else
    // auto vars = util::Slicer::process(a_struct_vars, ";");
    // for (auto& i : vars)
    // {
    //     auto parts    = util::Slicer::process(i, " \t\n[]");
    //     auto& cur_var = data.vars[cnt];
    //     if (parts[0] == "int")
    //     {
    //         cur_var = {CPPTypeEnum::INT, 4};
    //         data.str_max_size += 10;
    //     }
    //     else if (parts[0] == "float")
    //     {
    //         cur_var = {CPPTypeEnum::FLOAT, 4};
    //         data.str_max_size += 10;
    //     }
    //     else if (parts[0] == "bool")
    //     {
    //         cur_var = {CPPTypeEnum::BOOL, 1};
    //         data.str_max_size += 5;
    //     }
    //     else if (parts[0] == "char")
    //     {
    //         size_t temp = std::stoi(str::string(parts[2]));
    //         cur_var     = {CPPTypeEnum::CHAR_PTR, temp};
    //         data.str_max_size += temp + 2;
    //     }
    //     // TODO: safe
    //     strcpy(cur_var.name, str::string(parts[1]).c_str());

    //     ++cnt;
    // }

    data.count = cnt;

    return m_struct_data.size() - 1;
}

//--------------------------------------------------------------------------------

data::StructData&
data::StructStorage::getStructData(word_t a_struct_id) noexcept
{
    return getInstance().m_struct_data[a_struct_id];
}

void
data::StructStorage::shrinkToFit() noexcept
{
    getInstance().m_struct_data.shrink_to_fit();
}

size_t
data::StructStorage::getSize() noexcept
{
    return getInstance().m_struct_data.size();
}
