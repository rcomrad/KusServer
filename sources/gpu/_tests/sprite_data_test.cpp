#include "kernel/tester/fixture.hpp"

#include "gpu/sprite/sprite_push_data.hpp"
#include "gpu/sprite/sprite_view.hpp"
#include "gpu/sprite/texture_info.hpp"

namespace kustest
{

TEST(TextureInfoTest, DefaultsToSinglePixelWithoutAnimations)
{
    gpu::sprite::TextureInfo info;

    EXPECT_EQ(info.dimensions, gpu::type::Dimensions(1, 1));
    EXPECT_EQ(info.hitbox_offset, gpu::type::Coordinates(0, 0));
    EXPECT_TRUE(info.animation.empty());
}

TEST(SpriteViewTest, StoresIdentitySizeAndOffset)
{
    gpu::sprite::SpriteView view{3, gpu::type::CoordinateSize(64, 32),
                                 gpu::type::Coordinates(1, 2)};

    EXPECT_EQ(view.sprite_id, 3);
    EXPECT_EQ(view.size, gpu::type::CoordinateSize(64, 32));
    EXPECT_EQ(view.hitbox_offset, gpu::type::Coordinates(1, 2));
}

TEST(SpritePushDataTest, StoresPerSpriteTransformValues)
{
    gpu::sprite::SpritePushData push{};
    push.coord_scaler = {1.0f, 2.0f};
    push.coord_offset = {3.0f, 4.0f};
    push.uv_scaler    = {0.5f, 0.25f};
    push.uv_offset    = {0.125f, 0.75f};

    EXPECT_FLOAT_EQ(push.coord_scaler.x, 1.0f);
    EXPECT_FLOAT_EQ(push.coord_scaler.y, 2.0f);
    EXPECT_FLOAT_EQ(push.coord_offset.x, 3.0f);
    EXPECT_FLOAT_EQ(push.coord_offset.y, 4.0f);
    EXPECT_FLOAT_EQ(push.uv_scaler.x, 0.5f);
    EXPECT_FLOAT_EQ(push.uv_scaler.y, 0.25f);
    EXPECT_FLOAT_EQ(push.uv_offset.x, 0.125f);
    EXPECT_FLOAT_EQ(push.uv_offset.y, 0.75f);
}

} // namespace kustest
