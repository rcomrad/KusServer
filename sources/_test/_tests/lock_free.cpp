#include <atomic>
#include <queue>
#include <vector>

#include "kernel/tester/fixture.hpp"

namespace kustest
{

class ULockFreeTest : public Fixture
{
};

template <typename DataT, size_t BufferSize = 4>
class LockFreeQueue
{
    struct Node
    {
        // union forces not to call the constructor when creating
        union DataU
        {
            DataU()
            {
            }
            DataT value;
            char filler;
        } data;

        std::atomic<Node*> next;

        Node() : next(nullptr)
        {
        }
    };

public:
    LockFreeQueue()
    {
        m_head = m_tail = new Node;
    }

    template <typename... Args>
    void emplace(Args&&... args)
    {
        Node* new_node = new Node;
        Node* cur      = m_head.exchange(new_node, std::memory_order_acq_rel);
        new (&cur->data) DataT(std::forward<Args>(args)...);
        cur->next.store(new_node, std::memory_order_release);
    }

    DataT& front()
    {
        Node* cur = m_tail;
        while (!m_tail.compare_exchange_strong(cur, cur->next,
                                               std::memory_order_acq_rel,
                                               std::memory_order_acquire));
        return cur->data.value;
    }

    void pop(DataT& a_data)
    {
        delete &a_data;
    }

private:
    std::atomic<Node*> m_head;
    std::atomic<Node*> m_tail;
};

struct Data
{
    int a;
    double b;
    char c;

    Data(int a_a, double a_b, char a_c) : a(a_a), b(a_b), c(a_c)
    {
    }

    bool operator==(const Data& other) const
    {
        return a == other.a && b == other.b && c == other.c;
    }
};

TEST_F(ULockFreeTest, smoke)
{
    LockFreeQueue<Data> queue;
    queue.emplace(2, 3.4, 'f');
    auto& d = queue.front();
    Data answer(2, 3.4, 'f');
    EXPECT_EQ(answer, d);
    queue.pop(d);
}

enum class ActionTypes
{
    EMPLACE,
    FRONT,
    POP
};

TEST_F(ULockFreeTest, singL_thread)
{
    std::vector<ActionTypes> actions;

    LockFreeQueue<Data> my_queue;
    std::queue<Data> std_queue;

    for (auto action : actions)
    {
        switch (action)
        {
            case ActionTypes::EMPLACE:
                /* code */
                break;
            case ActionTypes::FRONT:
                /* code */
                break;
            case ActionTypes::POP:
                /* code */
                break;
        }
    }

    // queue.emplace(2, 3.4, "f");
    // queue.emplace(7, -0.001, "z");
    // auto& d1 = queue.get();
    // EXPECT_EQ(sizeof(Double), 8);
    // queue.emplace(-3, 0, "a");
    // queue.pop();
    // auto& d2 = queue.get();
    // EXPECT_EQ(sizeof(Double), 8);
    // queue.emplace(10, -1, "Z");
    // queue.emplace(0, 7, "A");
    // queue.emplace(0, 999.999, "Q");
}

// template <typename DataT, size_t BufferSize = 4>
// class LockFreeQueue
// {
// public:
//     void pop();

//     template <typename... Args>
//     void emplace(Args&&... args)
//     {
//         new (m_data + m_write) DataT(std::forward<Args>(args)...);
//     }

// private:
//     std::atomic<int> m_read;
//     std::atomic<int> m_write;
//     DataT m_data[BufferSize];
// };

//--------------------------------------------------------------------------------

} // namespace kustest
