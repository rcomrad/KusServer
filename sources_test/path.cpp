#include "utility/file_system/path.hpp"

#include <gtest/gtest.h>

TEST(PathCombine, test_combine_file_3_words)
{

    std::string path = util::Path::combine<std::string_view>(
        false, "user", "Desktop", "kus.png");

    EXPECT_STREQ(path.c_str(), "user/Desktop/kus.png");
}
TEST(PathCombine, test_combine_folder_3_words)
{
    std::string path =
        util::Path::combine<std::string_view>(true, "user", "Desktop", "kus");

    EXPECT_STREQ(path.c_str(), "user/Desktop/kus/");
}

TEST(PathCombine, test_combine_file_1_word)
{

    std::string path =
        util::Path::combine<std::string_view>(false, "us!!dD  Der.png");

    EXPECT_STREQ(path.c_str(), "us!!dD  Der.png");
}
TEST(PathCombine, test_combine_folder_1_word)
{
    std::string path =
        util::Path::combine<std::string_view>(true, "useR  WQr/");

    EXPECT_STREQ(path.c_str(), "useR  WQr/");
}

///////////////////////////////////////////////////////////////////////////////////////////////////

TEST(PathGetName, test_get_name_file)
{
    DECLARE_LOCAL_CONTEXT;

    std::string path = util::Path::combine<std::string_view>(
        false, "user", "Desktop", "kus.png");

    ASSERT_STREQ(path.c_str(), "user/Desktop/kus.png");

    std::string name = util::Path::getName(path, context_local);

    EXPECT_STREQ(name.c_str(), "kus.png");
}

TEST(PathGetName, test_get_name_folder)
{
    DECLARE_LOCAL_CONTEXT;

    std::string path =
        util::Path::combine<std::string_view>(true, "user", "Desktop", "kus");

    ASSERT_STREQ(path.c_str(), "user/Desktop/kus/");

    std::string name = util::Path::getName(path, context_local);

    EXPECT_STREQ(name.c_str(), "kus");
}

///////////////////////////////////////////////////////////////////////////////////////////////////

TEST(PathNormalizeFolderPath, test_normalize_folder_path_with_sep_postfix)
{
    DECLARE_LOCAL_CONTEXT;

    std::string path =
        util::Path::combine<std::string_view>(true, "user", "Desktop", "kus");

    ASSERT_STREQ(path.c_str(), "user/Desktop/kus/");

    std::string normalize_folder_path =
        util::Path::normalizeFolderPath(path, true);

    EXPECT_STREQ(normalize_folder_path.c_str(), "user/Desktop/kus/");
}

TEST(PathNormalizeFolderPath, test_normalize_folder_path_without_sep_postfix)
{
    DECLARE_LOCAL_CONTEXT;

    std::string path =
        util::Path::combine<std::string_view>(true, "user", "Desktop", "kus");

    ASSERT_STREQ(path.c_str(), "user/Desktop/kus/");

    std::string normalize_folder_path =
        util::Path::normalizeFolderPath(path, false);

    EXPECT_STREQ(normalize_folder_path.c_str(), "user/Desktop/kus");
}

TEST(PathNormalizeFolderPath, test_normalize_folder_path_with_sep_postfix_2)
{
    DECLARE_LOCAL_CONTEXT;

    std::string path = "user/Desktop/kus";

    std::string normalize_folder_path =
        util::Path::normalizeFolderPath(path, true);

    EXPECT_STREQ(normalize_folder_path.c_str(), "user/Desktop/kus/");
}

TEST(PathNormalizeFolderPath, test_normalize_folder_path_without_sep_postfix_2)
{
    DECLARE_LOCAL_CONTEXT;

    std::string path = "user/Desktop/kus";

    std::string normalize_folder_path =
        util::Path::normalizeFolderPath(path, false);

    EXPECT_STREQ(normalize_folder_path.c_str(), "user/Desktop/kus");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(PathGetRelativeToApp, test_get_relative_to_app_folder)
{
    DECLARE_LOCAL_CONTEXT;

    std::string path = util::Path::combine<std::string_view>(
        true, "fi??rst", "se con d", "thi!!rd");

    ASSERT_STREQ(path.c_str(), "fi??rst/se con d/thi!!rd/");

    std::string normalize_folder_path =
        util::Path::normalizeFolderPath(path, true);

    ASSERT_STREQ(normalize_folder_path.c_str(), "fi??rst/se con d/thi!!rd/");

    std::string full_path =
        "/home/arsen/Desktop/KusServer/fi??rst/se con d/thi!!rd/";

    // /home/arsen/Desktop/KusServer/
    EXPECT_STREQ(
        util::Path::getRelativeToApp(normalize_folder_path, true).c_str(),
        full_path.c_str());
}

TEST(PathGetRelativeToApp, test_get_relative_to_app_file)
{
    DECLARE_LOCAL_CONTEXT;

    std::string path = util::Path::combine<std::string_view>(
        false, "fi??rst", "se con d", "thi!!rd.png");

    ASSERT_STREQ(path.c_str(), "fi??rst/se con d/thi!!rd.png");

    std::string full_path =
        "/home/arsen/Desktop/KusServer/fi??rst/se con d/thi!!rd.png";

    // /home/arsen/Desktop/KusServer/
    EXPECT_STREQ(util::Path::getRelativeToApp(path, false).c_str(),
                 full_path.c_str());
}
