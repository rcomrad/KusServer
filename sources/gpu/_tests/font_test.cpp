#include "kernel/framework/logger/basic/exception.hpp"
#include "kernel/tester/fixture.hpp"

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "gpu/font/font.hpp"
#include "gpu/font/font_storage.hpp"
#include "gpu/sprite/draw_task.hpp"
#include "gpu/sprite/sprite_view.hpp"

namespace kustest
{

namespace
{

std::unordered_map<char, gpu::sprite::SpriteView>
makeCharSprites()
{
    std::unordered_map<char, gpu::sprite::SpriteView> result;
    result.emplace('A', gpu::sprite::SpriteView{
                            5, gpu::type::CoordinateSize(64, 64),
                            gpu::type::Coordinates(0, 0)});
    result.emplace('B', gpu::sprite::SpriteView{
                            6, gpu::type::CoordinateSize(64, 64),
                            gpu::type::Coordinates(0, 0)});
    return result;
}

} // namespace

TEST(FontTest, EmptyTextProducesNoDrawTasks)
{
    gpu::font::Font font(makeCharSprites());
    std::vector<gpu::sprite::DrawTask> tasks;

    EXPECT_NO_THROW(font.writeText("", {10, 20}, tasks));
    EXPECT_TRUE(tasks.empty());
}

TEST(FontTest, WritesOneTaskPerCharacter)
{
    gpu::font::Font font(makeCharSprites());
    std::vector<gpu::sprite::DrawTask> tasks;

    font.writeText("AB", {10, 20}, tasks);

    EXPECT_EQ(tasks.size(), 2u);
}

TEST(FontTest, UnknownCharacterThrows)
{
    gpu::font::Font font(makeCharSprites());
    std::vector<gpu::sprite::DrawTask> tasks;

    EXPECT_THROW(font.writeText("C", {10, 20}, tasks),
                 core::LoggerException);
}

TEST(FontStorageTest, FindsRegisteredFontAndRejectsUnknownName)
{
    std::vector<gpu::font::Font> fonts;
    fonts.emplace_back(makeCharSprites());

    std::unordered_map<std::string, int> names;
    names.emplace("main", 0);

    gpu::font::FontStorage storage(std::move(fonts), std::move(names));

    EXPECT_EQ(storage.getFontId("main"), 0);
    EXPECT_THROW(storage.getFontId("missing"), core::LoggerException);
}

TEST(FontStorageTest, WritesTextThroughRegisteredFont)
{
    std::vector<gpu::font::Font> fonts;
    fonts.emplace_back(makeCharSprites());

    std::unordered_map<std::string, int> names;
    names.emplace("main", 0);

    gpu::font::FontStorage storage(std::move(fonts), std::move(names));
    std::vector<gpu::sprite::DrawTask> tasks;

    EXPECT_NO_THROW(storage.writeText("AB", {0, 0}, 0, tasks));
    EXPECT_EQ(tasks.size(), 2u);
}

} // namespace kustest
