#include "kernel/tester/fixture.hpp"

#include "gpu/event/event.hpp"

namespace kustest
{

TEST(EventTest, MousePositionSetsTypeAndPayload)
{
    gpu::event::MousePosition position;
    position.coord    = {12, 34};
    position.is_valid = true;

    gpu::event::Event event(position);

    EXPECT_EQ(event.type, gpu::event::EventType::MousePositionEvent);
    EXPECT_EQ(event.mousePosition.coord, gpu::type::Coordinates(12, 34));
    EXPECT_TRUE(event.mousePosition.is_valid);
}

TEST(EventTest, MouseInputSetsTypeAndPayload)
{
    gpu::event::MouseInput input{1, 2};

    gpu::event::Event event(input);

    EXPECT_EQ(event.type, gpu::event::EventType::MouseInputEvent);
    EXPECT_EQ(event.mouseInput.button, 1);
    EXPECT_EQ(event.mouseInput.type, 2);
}

TEST(EventTest, KeyInputSetsTypeAndPayload)
{
    gpu::event::KeyInput input{3, 4};

    gpu::event::Event event(input);

    EXPECT_EQ(event.type, gpu::event::EventType::KeyInputEvent);
    EXPECT_EQ(event.keyInput.key, 3);
    EXPECT_EQ(event.keyInput.type, 4);
}

} // namespace kustest
