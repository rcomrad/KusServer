#ifndef DRAWABLE_SYSTEM_STORAGE_HPP
#define DRAWABLE_SYSTEM_STORAGE_HPP
#include <string>
#include <tuple>
#include <unordered_map>

namespace kusengine
{
namespace render
{
template <typename DrawableSystem_T>
class DrawableSystemStorage
{
public:
    using DrawableSystemType = DrawableSystem_T;

    template <typename Iterator>
    void add(const std::string& key, Iterator begin, Iterator end);

    const DrawableSystem_T& getDrawableSystem(
        const std::string& key) const& noexcept;

private:
    std::unordered_map<std::string, DrawableSystem_T> m_dr_system_storage;
};

template <typename DrawableSystem_T>
template <typename Iterator>
void
DrawableSystemStorage<DrawableSystem_T>::add(const std::string& key,
                                             Iterator begin,
                                             Iterator end)
{
    if (m_dr_system_storage.find(key) != m_dr_system_storage.end())
    {
        throw "drawable_system added second time\n";
    }
    m_dr_system_storage[key].resetDrawables(begin, end);
}

template <typename DrawableSystem_T>
const DrawableSystem_T&
DrawableSystemStorage<DrawableSystem_T>::getDrawableSystem(
    const std::string& key) const& noexcept
{
    return m_dr_system_storage.at(key);
}

}; // namespace render
}; // namespace kusengine

#endif // DRAWABLE_SYSTEM_STORAGE_HPP
