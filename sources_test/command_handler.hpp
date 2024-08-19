// #include "core/command/input_buffer.hpp"
// #include "core/condvar.hpp"
// #include "core_loop.hpp"

// #include "fixture.hpp"

// namespace kustest
// {
// using VarMap = std::unordered_map<std::string, int>;
// class CommandHandler : public Fixture, public CoreLoop
// {
// private:
//     struct BufferContiext
//     {
//         std::string buffer;
//         core::Condvar flag;
//     };

// public:
//     CommandHandler() noexcept;
//     ~CommandHandler() noexcept;

//     template <typename S>
//     std::string execCommand(S&& a_command) const noexcept
//     {
//         BufferContiext result;
//         core::CommandReader::sendToBuffer(std::forward<S>(a_command),
//                                           (void*)&result);
//         result.flag.wait();
//         return result.buffer;
//     }

//     auto lineriseResult(std::string& a_data) const noexcept;

//     VarMap getVariableMap() const noexcept;

//     static void bufferOutput(const char* a_buff, void* a_context) noexcept;
// };

// } // namespace kustest
