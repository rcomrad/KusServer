#ifndef DRAWABLE_SYSTEM_STORAGE_HPP
#define DRAWABLE_SYSTEM_STORAGE_HPP
#include <string>
#include <unordered_map>

namespace kusengine
{
namespace render
{
template <typename DrawableSystemType>
class DrawableSystemStorage
{
public:
    template <typename Iterator>
    std::string add(const std::string& key, Iterator begin, Iterator end);

    void draw(const std::string& key);

private:
    std::unordered_map<std::string, DrawableSystemType> m_dr_system_storage;
};
template <typename DrawableSystemType>
template <typename Iterator>
std::string
DrawableSystemStorage<DrawableSystemType>::add(const std::string& key,
                                               Iterator begin,
                                               Iterator end)
{
    if (m_dr_system_storage.find(key) != m_dr_system_storage.end())
    {
        return key + "+";
    }
    m_dr_system_storage[key].resetDrawables(begin, end);
    return key;
}

template <typename DrawableSystemType>
void
DrawableSystemStorage<DrawableSystemType>::draw(const std::string& key)
{
	// m_dr_system_storage[key]
}

}; // namespace render
}; // namespace kusengine

#endif // DRAWABLE_SYSTEM_STORAGE_HPP
