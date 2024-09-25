#include "utility/file_system/path.hpp"

#include <gtest/gtest.h>

#include "utility/file_system/path_storage.hpp"
#include "utility/file_system/path_values.hpp"
// Simple tests for PathCombine and PathGetName
//------------------------------------------------------------------------------
TEST(PathCombineAndGetName, test_combine_and_getName_3_words)
{
    DECLARE_LOCAL_CONTEXT;

    std::string path = util::Path::combine(false, "user", "Desktop", "kus.png");
    ASSERT_EQ(path, "user/Desktop/kus.png");
    std::string name = util::Path::getName(path, context_local);
    EXPECT_EQ(name, "kus.png");

    path = util::Path::combine(true, "user", "Desktop", "kus");
    ASSERT_EQ(path, "user/Desktop/kus/");
    name = util::Path::getName(path, context_local);
    EXPECT_EQ(name, "kus");
}
//------------------------------------------------------------------------------
// Difficult tests for PathCombine
//------------------------------------------------------------------------------
TEST(PathCombineAndGetName, test_combine_and_getName_1_word)
{
    DECLARE_LOCAL_CONTEXT;

    std::string path = util::Path::combine(false, "us!!dD  Der.png");
    ASSERT_EQ(path, "us!!dD  Der.png");
    std::string name = util::Path::getName(path, context_local);
    EXPECT_EQ(name, "us!!dD  Der.png");

    path = util::Path::combine(true, "useR  WQr/");
    ASSERT_EQ(path, "useR  WQr/");
    name = util::Path::getName(path, context_local);
    EXPECT_EQ(name, "useR  WQr");
}
//------------------------------------------------------------------------------

// Simple tests for PathNormalizeFolderPath
//------------------------------------------------------------------------------
TEST(PathNormalizeFolderPath,
     test_normalize_folder_path_with_sep_postfix_in_initial_path)
{
    std::string path = "user/Desktop/kus/";
    std::string normalize_folder_path =
        util::Path::normalizeFolderPath(path, true);
    EXPECT_EQ(normalize_folder_path, "user/Desktop/kus/");

    normalize_folder_path = util::Path::normalizeFolderPath(path, false);
    EXPECT_EQ(normalize_folder_path, "user/Desktop/kus");
}

TEST(PathNormalizeFolderPath,
     test_normalize_folder_path_without_sep_postfix_in_initial_path)
{
    std::string path = "user/Desktop/kus";
    std::string normalize_folder_path =
        util::Path::normalizeFolderPath(path, true);
    EXPECT_EQ(normalize_folder_path, "user/Desktop/kus/");

    normalize_folder_path = util::Path::normalizeFolderPath(path, false);
    EXPECT_EQ(normalize_folder_path, "user/Desktop/kus");
}
//------------------------------------------------------------------------------

// Simple tests for PathGetRelativeToApp
//------------------------------------------------------------------------------
TEST(PathGetRelativeToApp, test_get_relative_to_app_folder)
{

    std::string path = "fi??rst/se con d/thi!!rd/";

    DECLARE_LOCAL_CONTEXT;
    
    auto app_path =
        util::PathStorage::getFolderPath(util::APP_PATH_NAME, &context_local);

    std::string full_path = app_path.value().data();
    full_path += "fi??rst/se con d/thi!!rd/";

    EXPECT_EQ(util::Path::getRelativeToApp(path, true), full_path);
}

TEST(PathGetRelativeToApp, test_get_relative_to_app_file)
{

    std::string path = "fi??rst/se con d/thi!!rd.png";

    DECLARE_LOCAL_CONTEXT;

    auto app_path =
        util::PathStorage::getFolderPath(util::APP_PATH_NAME, &context_local);

    std::string full_path = app_path.value().data();
    full_path += "fi??rst/se con d/thi!!rd.png";

    EXPECT_EQ(util::Path::getRelativeToApp(path, false), full_path);
}
//------------------------------------------------------------------------------
