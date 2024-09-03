#include "command_data.hpp"

#include "utility/string/slicer.hpp"

core::CommandData::CommandData(std::string&& a_comm_str) noexcept
{
    m_data    = std::move(a_comm_str);
    auto args = util::Slicer::process(m_data, "; \n\t");

    // first word is a command and processed separately
    value = args[0];

    for (int i = 1; i < args.size(); ++i)
    {
        auto temp = util::Slicer::process(args[i], "=");
        if (temp.size() == 1)
        {
            arguments.emplace_back(temp[0]);
        }
        else
        {
            variables[temp[0]] = temp[1];
        }
    }
}
