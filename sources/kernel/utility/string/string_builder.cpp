#include "string_builder.hpp"

#include "kernel/framework/logger/include_me.hpp"

util::StringBuilder::StringBuilder()
    : m_size(0), m_sep_start(0), m_sep_ptr(nullptr)
{
    m_data_array.reserve(100);
}

std::unique_ptr<char[]>
util::StringBuilder::collapse()
{
    if (m_sep_ptr)
    {
        m_sep_ptr->collapse();
    }

    std::unique_ptr<char[]> result = std::make_unique<char[]>(m_size + 1);
    auto ptr                       = result.get();

    char sep = 0;
    int gg   = 0;
    for (auto& i : m_data_array)
    {
        auto old = ptr;
        switch (i.type)
        {
            case Type::NUM_S32:
                if (sep)
                {
                    ptr += sprintf(ptr, "%d%c", i.data.num_s32, sep);
                }
                else
                {
                    ptr += sprintf(ptr, "%d", i.data.num_s32);
                }
                break;
            case Type::STRING_VIEW:
                if (sep)
                {
                    ptr += sprintf(ptr, "%s%c", i.data.str.data(), sep);
                }
                else
                {
                    ptr += sprintf(ptr, "%s", i.data.str.data());
                }
                break;
            case Type::CHAR:
                ptr += sprintf(ptr, "%c", i.data.char_val);
                break;
            case Type::SEPARATOR:
                sep = i.data.char_val;
                break;
            case Type::POP_BACK:
                --ptr;
                break;
            default:
                // error
                break;
        }
        gg += ptr - old;
    }
    *ptr = 0;

    if (gg >= m_size + 1) THROW("Statement size exceeded memory buffer");

    m_data_array.clear();
    if (m_sep_ptr)
    {
        m_sep_ptr->subscribe();
    }

    return result;
}

util::StringBuilder::Data::Data()
{
}

util::StringBuilder::Entry::Entry(Type a_type) : type(a_type)
{
}

void
util::StringBuilder::add(char a_data)
{
    m_data_array.emplace_back(Type::CHAR).data.char_val = a_data;
    m_size += 1;
}

void
util::StringBuilder::add(int a_data)
{
    m_data_array.emplace_back(Type::NUM_S32).data.num_s32 = a_data;
    m_size += 10;
}

void
util::StringBuilder::add(std::string_view a_data)
{
    m_data_array.emplace_back(Type::STRING_VIEW).data.str = a_data;
    m_size += a_data.size();
}

void
util::StringBuilder::addDBData(int a_data)
{
    add(a_data);
}

void
util::StringBuilder::addDBData(std::string_view a_data)
{
    add('\'');
    m_data_array.emplace_back(Type::STRING_VIEW).data.str = a_data;
    add('\'');
    m_size += a_data.size() + 2;
}

util::StringBuilder::ScopedSeparator
util::StringBuilder::addSeparator(char a_sep)
{
    ScopedSeparator result(*this, a_sep);
    result.subscribe();
    return result;
}

void
util::StringBuilder::pop_back()
{
    m_data_array.emplace_back(Type::POP_BACK);
}

util::StringBuilder::ScopedSeparator::ScopedSeparator(StringBuilder& a_sb_ref,
                                                      char a_sep)
    : m_sb_ref(a_sb_ref), m_is_collapsed(false), m_sep(a_sep)
{
}

util::StringBuilder::ScopedSeparator::~ScopedSeparator()
{
    if (!m_is_collapsed)
    {
        collapse();
    }
}

void
util::StringBuilder::ScopedSeparator::subscribe()
{
    m_sb_ref.m_sep_start = m_sb_ref.m_data_array.size();
    m_sb_ref.m_data_array.emplace_back(Type::SEPARATOR).data.char_val = m_sep;

    m_is_collapsed = false;
}

void
util::StringBuilder::ScopedSeparator::collapse()
{
    m_sb_ref.m_size += m_sb_ref.m_data_array.size() - m_sb_ref.m_sep_start;
    m_sb_ref.m_data_array.emplace_back(Type::SEPARATOR).data.char_val = 0;

    m_is_collapsed = true;
}
