#ifndef PARSER_BASIC_FUNCTIONS_HPP
#define PARSER_BASIC_FUNCTIONS_HPP
#include <glm/vec2.hpp>
#include <nlohmann/json.hpp>

namespace nlohmann
{
template <>
struct adl_serializer<glm::vec2>
{
    static void to_json(json& j, const glm::vec2& obj)
    {
        j = json{
            {"x", obj.x},
            {"y", obj.y}
        };
    }

    static void from_json(const json& j, glm::vec2& obj)
    {
        j.at("x").get_to(obj.x);
        j.at("y").get_to(obj.y);
    }
};
} // namespace nlohmann

#endif // PARSER_BASIC_FUNCTIONS_HPP
