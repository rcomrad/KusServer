#include "vertex.hpp"

namespace kusengine::render
{
Vertex::Vertex(Type vt, int count) : m_data(count), m_type(vt)
{
}

int
Vertex::floatCount() const noexcept
{
    return m_data.size();
}

void
Vertex::pushTo(std::vector<float>& arr)
{
    for (int i = 0; i < m_data.size(); ++i)
    {
        arr.emplace_back(m_data[i]);
    }
}

void
Vertex::setValue(float value, int index) noexcept
{
    m_data[index] = value;
}

} // namespace kusengine::render
