#ifndef CACHE_HPP
#define CACHE_HPP

namespace kusengine::render
{
template <typename T>
class Cache
{
public:
    void cache(const T& t)
    {
        m_cache = t;
    }

    bool isInCache(const T& t) const noexcept
    {
        return t == m_cache;
    }

private:
    T m_cache;
};
} // namespace kusengine::render

#endif // CACHE_HPP
