#include "kernel/tester/fixture.hpp"

#include "gpu/sprite/animation.hpp"

namespace kustest
{

class TestAnimation : public gpu::sprite::Animation
{
public:
    explicit TestAnimation(const gpu::sprite::TextureInfo& a_info);

    using Animation::drawAnimation;
};

class AnimationTest : public Fixture
{
    using AnimationMap = std::unordered_map<std::string, std::vector<int>>;

public:
    void setDementions(int a_x, int a_y);
    void setAnimation(AnimationMap&& a_map);

    TestAnimation constructAnimation();

    void checkAllOffsets(TestAnimation const& a_animation);

private:
    int m_dem_x = 0;
    int m_dem_y = 0;

    AnimationMap m_anim_map;

    void checkPushOffset(TestAnimation const& a_animation,
                         int a_frame_num,
                         double a_x,
                         double a_y);
};

} // namespace kustest
