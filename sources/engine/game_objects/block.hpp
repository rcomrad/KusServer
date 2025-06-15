#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "templates/block_template.hpp"

#include "game_object.hpp"

namespace kusengine
{

struct BlockCreateArgs
{
    glm::vec2 position;
    glm::vec2 size;
    int current_hp;

    std::string texture_name;
};

class Block final : public GameObject
{
public:
    Block(std::shared_ptr<const BlockTemplate> bl_temp,
          const BlockCreateArgs& args);

    void logic() override;

    // bool readParameters(std::stringstream& ss) override;

protected:
    std::shared_ptr<const BlockTemplate> m_block_template;

    int m_current_hp;
};

}; // namespace kusengine

#endif // BLOCK_HPP
