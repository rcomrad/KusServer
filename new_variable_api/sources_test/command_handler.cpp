// #include "command_handler.hpp"

// #include "core/command_reader.hpp"
// #include "core/core.hpp"

// #include "file_system/file_read.hpp"

// #include "utility/string/slicer.hpp"

// kustest::CommandHandler::CommandHandler() noexcept
// {
//     core::CommandReader::bufferUsage(true);
//     core::CommandReader::setOutputCallback(bufferOutput);
// }

// kustest::CommandHandler::~CommandHandler() noexcept
// {
//     core::CommandReader::bufferUsage(false);
//     core::CommandReader::setOutputCallback();
// }

// auto
// kustest::CommandHandler::lineriseResult(std::string& a_data) const noexcept
// {
//     auto result = fs::FileRead::getLines(fs::DataTarget(a_data));
//     result.erase(result.begin());
//     return result;
// }

// kustest::VarMap
// kustest::CommandHandler::getVariableMap() const noexcept
// {
//     auto output = execCommand("var_show");
//     auto lines  = lineriseResult(output);
//     lines.erase(lines.begin());
//     lines.pop_back();
//     VarMap result;
//     for (auto& i : lines)
//     {
//         auto parts       = util::Slicer::process(i, "=", " \t'");
//         result[parts[0]] = std::stoi(parts[1]);
//     }
//     return result;
// }

// void
// kustest::CommandHandler::bufferOutput(const char* a_buff,
//                                       void* a_context) noexcept
// {
//     BufferContiext& context = *static_cast<BufferContiext*>(a_context);
//     context.buffer          = std::string(a_buff);
//     context.flag.notify();
// }
