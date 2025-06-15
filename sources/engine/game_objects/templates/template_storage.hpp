#ifndef TEMPLATE_STORAGE_HPP
#define TEMPLATE_STORAGE_HPP

#include <nlohmann/json.hpp>

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include "template.hpp"

namespace kusengine
{

struct SomeTempararyData
{
    std::string texture_name;
};

class TemplateStorage
{
public:
    static TemplateStorage& getInstance();

    void loadData();

    std::optional<std::pair<std::shared_ptr<Template>, SomeTempararyData>>
    getTemplate(std::string_view key) const;

private:
    TemplateStorage() = default;

    // load funcions//

    void loadBlocks(const nlohmann::json_abi_v3_11_3::json& json);

    void loadAnimals(const nlohmann::json_abi_v3_11_3::json& json);

    // ----------- //

    std::map<std::string,
             std::pair<std::shared_ptr<Template>, SomeTempararyData>>
        m_template_storage;
};

#define TEMPLATE_STORAGE TemplateStorage::getInstance()

}; // namespace kusengine

#endif // TEMPLATE_STORAGE_HPP
