// #pragma once

// #include <atomic>

// namespace utils
// {

// template <typename Data>
// class AtomicDuplicate
// {
// public:
//     AtomicDuplicate() : m_state(0)
//     {
//     }

//     Data& acquireRead()
//     {
//         uint8_t temp = m_state.load(std::memory_order_acquire);
//         if (temp & 1)
//         {
//             temp++;
//             m_state.store(temp, std::memory_order_release);
//         }
//         return temp & 2 ? m_first : m_second;
//     }

//     Data& acquireWrite()
//     {
//         uint8_t temp = m_state.load(std::memory_order_acquire);
//         if (!(temp & 1))
//         {
//             temp++;
//             m_state.store(temp, std::memory_order_release);
//         }
//         return temp & 2 ? m_second : m_first;
//     }

// private:
//     Data m_first;
//     Data m_second;
//     std::atomic<uint8_t> m_state;
// };

// } // namespace utils
