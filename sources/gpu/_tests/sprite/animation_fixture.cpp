#include "animation_fixture.hpp"

#include "gpu/sprite/sprite_push_data.hpp"
#include "gpu/sprite/texture_info.hpp"

namespace kustest
{

TestAnimation::TestAnimation(const gpu::sprite::TextureInfo& a_info)
    : Animation(a_info)
{
}

void
AnimationTest::setDementions(int a_x, int a_y)
{
    m_dem_x = a_x;
    m_dem_y = a_y;
}
void
AnimationTest::setAnimation(AnimationMap&& a_map)
{
    m_anim_map = std::move(a_map);
}

TestAnimation
AnimationTest::constructAnimation()
{
    gpu::sprite::TextureInfo info;
    info.dimensions = gpu::type::Dimensions(m_dem_x, m_dem_y);
    info.animation  = m_anim_map;
    return TestAnimation(info);
}

void
AnimationTest::checkAllOffsets(TestAnimation const& a_animation)
{
    int num = 0;
    for (int i = 0; i < m_dem_x; ++i)
    {
        for (int j = 0; j < m_dem_y; ++j)
        {
            double x = 1. / m_dem_x * i;
            double y = 1. / m_dem_y * j;
            checkPushOffset(a_animation, num, x, y);
            ++num;
        }
    }
    EXPECT_GT(num, 0);
}

void
AnimationTest::checkPushOffset(TestAnimation const& a_animation,
                               int a_frame_num,
                               double a_x,
                               double a_y)
{
    auto benchmark = constructWithGarbage<gpu::sprite::SpritePushData>();
    gpu::sprite::SpritePushData tested = benchmark;

    benchmark.uv_scaler.x = 1. / m_dem_x;
    benchmark.uv_scaler.y = 1. / m_dem_y;

    benchmark.uv_offset.x = a_x;
    benchmark.uv_offset.y = a_y;

    a_animation.drawAnimation(tested, a_frame_num);
    EXPECT_EQ(tested, benchmark);
}

} // namespace kustest
