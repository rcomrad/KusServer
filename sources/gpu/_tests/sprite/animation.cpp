#include "animation_fixture.hpp"

namespace kustest
{

TEST_F(AnimationTest, DrawsUVScalerAndOffsetForEachFrame)
{
    setDementions(2, 3);
    setAnimation({
        {"idle", std::vector<int>{0, 1}}
    });

    auto animation = constructAnimation();
    checkAllOffsets(animation);
}

TEST_F(AnimationTest, CurrentFrameLookupReturnsRequestedFrame)
{
    auto animation = constructAnimation();

    // getAnimationFrame is currently a placeholder; the test documents the
    // existing behavior and should be updated when time-based animation lands.
    EXPECT_EQ(animation.getAnimationFrame(7, 100).value, 7);
}

} // namespace kustest
