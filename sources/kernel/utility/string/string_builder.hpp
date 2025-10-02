#pragma once

//--------------------------------------------------------------------------------

#include <memory>
#include <string>
#include <string_view>
#include <vector>

//--------------------------------------------------------------------------------

namespace util
{

class StringBuilder
{
    class [[nodiscard]] ScopedSeparator
    {
    public:
        ScopedSeparator(StringBuilder& a_sb_ref, char a_sep);
        ~ScopedSeparator();

        // TODO: private
        void subscribe();
        void collapse();

    private:
        StringBuilder& m_sb_ref;
        bool m_is_collapsed;
        char m_sep;
    };

public:
    StringBuilder();

    std::unique_ptr<char[]> collapse();

    void add(int a_data);
    void add(char a_data);
    void add(std::string_view a_data);
    void addQuotated(std::string_view a_data);

    ScopedSeparator addSeparator(char a_sep);

private:
    size_t m_size;

    union Data
    {
        Data();

        char char_val;
        int num_s32;
        std::string_view str;
    };
    enum class Type
    {
        NUN,
        CHAR,
        NUM_S32,
        STRING_VIEW,
        SEPARATOR
    };
    struct Entry
    {
        Type type;
        Data data;

        Entry(Type a_type);
    };

    int m_sep_start;
    ScopedSeparator* m_sep_ptr;
    std::vector<Entry> m_data_array;
};

} // namespace util

//--------------------------------------------------------------------------------
