#pragma once

#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/utility/type/declaration/pair.hpp"

#include <array>
#include <fstream>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#define MEMBER_CONCEPT(name) \
    template <typename T>    \
    concept HasFluid_##name = requires(T obj) { obj.name; };

MEMBER_CONCEPT(dimensions);
MEMBER_CONCEPT(hitbox_offset);
MEMBER_CONCEPT(animation);
MEMBER_CONCEPT(name);
MEMBER_CONCEPT(size);
MEMBER_CONCEPT(color);
MEMBER_CONCEPT(level);
MEMBER_CONCEPT(texture);
MEMBER_CONCEPT(text);
MEMBER_CONCEPT(ndc);
MEMBER_CONCEPT(coordinates);
MEMBER_CONCEPT(flags);
MEMBER_CONCEPT(type);

#define MEMBER_CHECK(name)               \
    if constexpr (HasFluid_##name<T>)    \
    {                                    \
        if (key == #name)                \
        {                                \
            if (!read(a_file, cur.name)) \
            {                            \
                THROW("Broken file");    \
            }                            \
            continue;                    \
        }                                \
    }

namespace core
{

class StructReader
{

protected:
    template <typename T>
    static std::unordered_map<std::string, T> readMap(std::ifstream&& a_file)
    {
        // constexpr auto members =
        // std::meta::nonstatic_data_members_of(^^T);

        std::unordered_map<std::string, T> result;
        auto it = result.end();

        std::string key;
        while (a_file >> key)
        {
            if (key.empty())
            {
                continue;
            }

            if (key.back() == '.')
            {
                key.pop_back();
                it = result.emplace(key, T()).first;
                continue;
            }
            auto& cur = it->second;

            if (key.back() == ':')
            {
                key.pop_back();

                // template for (constexpr auto member : members)
                // {
                //     constexpr std::string_view member_name =
                //         std::meta::identifier_of(member);

                //     if (key == member_name)
                //     {
                //         if (!read(a_file, cur.[:member:]))
                //         {
                //             THROW("Broken file");
                //         }
                //         continue;
                //     }
                // }
            }

            MEMBER_CHECK(dimensions);
            MEMBER_CHECK(hitbox_offset);
            MEMBER_CHECK(animation);
            MEMBER_CHECK(name);
            MEMBER_CHECK(size);
            MEMBER_CHECK(color);
            MEMBER_CHECK(level);
            MEMBER_CHECK(texture);
            MEMBER_CHECK(text);
            MEMBER_CHECK(ndc);
            MEMBER_CHECK(coordinates);
            MEMBER_CHECK(flags);
            MEMBER_CHECK(type);

            THROW("Unexpected string '%s'", key);
        }

        return result;
    }

private:
    // TODO: add errors?
    // using UnparsedT = std::optional<std::string>;

    // TODO: base type template + stoi/u/f ?

    static bool read(std::ifstream& a_file, int& a_num)
    {
        std::string temp;
        if (!basicRead(a_file, temp))
        {
            return false;
        }
        a_num = std::stoi(temp);
        return true;
    }

    static bool read(std::ifstream& a_file, unsigned& a_num)
    {
        std::string temp;
        if (!basicRead(a_file, temp))
        {
            return false;
        }
        a_num = std::stoul(temp);
        return true;
    }

    static bool read(std::ifstream& a_file, float& a_num)
    {
        std::string temp;
        if (!basicRead(a_file, temp))
        {
            return false;
        }
        a_num = std::stof(temp);
        return true;
    }

    static bool read(std::ifstream& a_file, std::string& a_str)
    {
        if (!basicRead(a_file, a_str))
        {
            return false;
        }
        return true;
    }

    template <typename T>
    static bool read(std::ifstream& a_file, std::optional<T>& a_opt)
    {
        T data;
        auto res = read(a_file, data);
        a_opt    = std::move(data);
        return res;
    }

    template <typename T1, typename T2>
    static bool read(std::ifstream& a_file, Pair<T1, T2>& a_pair)
    {
        return read(a_file, a_pair.i) && read(a_file, a_pair.j);
    }

    template <typename KeyT, typename ValueT>
    static bool read(std::ifstream& a_file,
                     std::unordered_map<KeyT, ValueT>& a_map)
    {
        arrayBeginAssert(a_file);

        while (true)
        {
            KeyT key;
            if (!read(a_file, key))
            {
                break;
            }

            ValueT value;
            if (!read(a_file, value))
            {
                break;
            }

            a_map.emplace(std::move(key), std::move(value));
        }

        return true;
    }

    template <typename ValueT, size_t ElementCount>
    static bool read(std::ifstream& a_file,
                     std::array<ValueT, ElementCount>& a_array)
    {
        arrayBeginAssert(a_file);

        int cnt = 0;
        while (true)
        {
            ValueT value;
            if (!read(a_file, value))
            {
                break;
            }

            a_array.at(cnt++) = std::move(value);
        }

        if (cnt != ElementCount)
        {
            THROW("Wrong array size: expected %d, found %d elements",
                  ElementCount, cnt);
        }

        return true;
    }

    template <typename ValueT>
    static bool read(std::ifstream& a_file, std::vector<ValueT>& a_vac)
    {
        arrayBeginAssert(a_file);

        while (true)
        {
            ValueT value;
            if (!read(a_file, value))
            {
                break;
            }

            a_vac.emplace_back(std::move(value));
        }

        return true;
    }

    static bool basicRead(std::ifstream& a_file, std::string& a_data)
    {
        a_data.clear();
        while (a_file >> a_data)
        {
            if (a_data.empty())
            {
                continue;
            }
            return !(a_data == "[" || a_data == "]");
        }
        return false;
    }

    static void arrayBeginAssert(std::ifstream& a_file)
    {
        std::string begin_char;
        auto res = basicRead(a_file, begin_char);
        if (res || begin_char != "[")
        {
            THROW("Unexpected array begin: no [ character");
        }
    }
};

} // namespace core
