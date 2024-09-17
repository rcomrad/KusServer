#pragma once

#include <typeindex>
#include <vector>

#include "table_info.hpp"
#include "table_storage.hpp"

#define BIG_LINE                                                               \
    "------------------------------------------------------------------------" \
    "------------------------------------------------------------------------" \
    "------------------------------------------------------------------------"

namespace core
{

class TablePrinter
{
public:
    template <typename T>
    static std::string print(T a_container,
                             std::vector<const char*> a_head) noexcept
    {
        a_head.insert(a_head.begin(), "#");
        const auto& info = TableStorage::getTableInfo(
            std::type_index(typeid(*a_container.begin())));

        std::vector<size_t> sizes(a_head.size());
        char* buffer     = nullptr;
        size_t line_size = 2;

        for (int i = 0; i < a_head.size(); ++i)
        {
            sizes[i] = strlen(a_head[i]) + 3;
        }

        int cnt = 1;
        for (const auto& i : a_container)
        {
            auto temp   = size_t(snprintf(nullptr, 0, " %d |", cnt++));
            sizes[0]    = std::max(sizes[0], temp);
            size_t indx = 1;
            print(info, reinterpret_cast<const char*>(&i), buffer, sizes, true,
                  indx);
        }

        for (auto& i : sizes)
        {
            line_size += i;
            // printf("%lu ", i);
        }
        // printf("\nline %lu\n", line_size);
        size_t cumulative_size = line_size * (a_container.size() + 4);
        // printf("size %lu\n", cumulative_size + 1);
        // TODO: should be +1, required +3 for some reason
        std::string result(cumulative_size + 10, 0);
        buffer = const_cast<char*>(result.c_str());

        snprintf(buffer, line_size, BIG_LINE);
        buffer += line_size;
        buffer += sprintf(buffer, "\n|");
        cnt = 0;
        for (int i = 0; i < a_head.size(); ++i, cnt++)
        {
            int offset = int(sizes[cnt] - 3);
            if (offset < 0) offset = 0;
            buffer += sprintf(buffer, " %-*s |", offset, a_head[cnt]);
        }
        snprintf(buffer, line_size, "\n" BIG_LINE);
        buffer += line_size + 1;
        buffer += sprintf(buffer, "\n");

        cnt = 1;
        for (const auto& i : a_container)
        {
            // TODO: code  works without it somehow, investigate
            // int offset = int(sizes[0] - 3);
            // if (offset < 0) offset = 0;
            buffer += sprintf(buffer, "| %-*d |", int(sizes[0] - 3), cnt++);
            size_t indx = 1;
            print(info, reinterpret_cast<const char*>(&i), buffer, sizes, false,
                  indx);
            buffer += sprintf(buffer, "\n");
        }
        snprintf(buffer, line_size, BIG_LINE);
        buffer += line_size;
        buffer += sprintf(buffer, "\n");
        // printf("expected: %lu actual: %lu last: %d last + 1: %d\n",
        //        cumulative_size + 1, result.size(), result[cumulative_size],
        //        result[cumulative_size + 1]);
        fflush(stdout);
        return result;
    }

    template <typename T>
    static std::string printRow(const T& a_obj,
                                std::vector<const char*> a_head) noexcept
    {
        std::vector<const T&> temp;
        temp.emplace_back(a_obj);
        return print(temp, a_head);
    }

private:
    static void print(const core::TableInfo& a_info,
                      const char* a_data_ptr,
                      char*& a_buffer,
                      std::vector<size_t>& a_sizes,
                      bool a_is_draft,
                      size_t& a_num) noexcept;

    static void printColumn(util::TypeID a_type,
                            const char* a_ptr,
                            char*& a_buffer,
                            std::vector<size_t>& a_sizes,
                            bool a_is_draft,
                            size_t& a_num) noexcept;
};

} // namespace core
