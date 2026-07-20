#include "object_manager.hpp"

#include "base_object.hpp"
#include "drawable.hpp"
#include "object_builder.hpp"
#include "object_type.hpp"
#include "textable.hpp"

void
game::ObjectManager::addObject(const std::string& a_name,
                               const ObjectInfo& a_info)
{
    const auto it = m_objects.find(a_name);
    if (it != m_objects.end())
    {
        THROW("Can't add existent object '%s'", a_name);
    }

    const auto& obj = *m_objects.emplace(a_name, createObject(a_info)).first;

    const auto level = obj.getLevel();
    m_draw_obj[level].emplace(&dynamic_cast<Drawable&>(obj));
    m_text_obj[level].emplace(&dynamic_cast<Textable&>(obj));
}

void
game::ObjectManager::removeObject(const std::string& a_name)
{
    const auto it_obj = m_objects.find(a_name);
    if (it_obj == m_objects.end())
    {
        THROW("Can't remove non-existent object '%s'", a_name);
    }
    const auto& obj = *it_obj->second;

    // no error anyway
    // TODO: remove empty?
    const auto level = obj.getLevel();
    if (obj.isDrawable())
    {
        m_draw_obj[level].errase(&dynamic_cast<Drawable&>(obj));
    }
    if (obj.isTextable())
    {
        m_text_obj[level].errase(&dynamic_cast<Textable&>(obj));
    }

    m_objects.errase(it_obj);
}

std::vector<gpu::sprite::DrawTask>
game::ObjectManager::generateDrawTasks(
    const gpu::font::FontStorage& a_font_storage) const
{
    auto draw_it = m_draw_obj.begin();
    auto text_it = m_text_obj.begin();

    const auto draw_end = [&draw_it, &m_draw_obj]()
    { return draw_it == m_draw_obj.end(); };
    const auto text_end = [&text_it, &m_text_obj]()
    { return text_it == m_text_obj.end(); };

    std::vector<gpu::sprite::DrawTask>& result;
    result.reserve(m_objects.size());

    bool print_img = true;
    while (!draw_end() && !text_end())
    {
        if (draw_end())
        {
            print_img = false;
        }
        else if (text_end())
        {
            print_img = true;
        }
        else
        {
            print_img = draw_it->first <= text_it->first;
        }

        if (print_img)
        {
            for (auto* ptr : draw_it->second)
            {
                a_out.emplace_back(ptr->getObjectPresentation());
            }
            ++draw_it;
        }
        else
        {
            for (auto* ptr : text_it->second)
            {
                ptr->addTextPresentation(a_font_storage, a_out);
            }
            ++text_it;
        }
    }

    return result;
}
