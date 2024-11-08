#include "utility/file_system/path_storage.hpp"

#include <gtest/gtest.h>

#include <array>
#include <filesystem>

// Simple tests for PathStorageGetFolderPath
//------------------------------------------------------------------------------

TEST(PathStorageGetFolderPath, test_get_folder_path)
{
    //.vscode
    auto folder_path = util::PathStorage::getFolderPath(".vscode");

    ASSERT_TRUE(folder_path.has_value());

    std::string correct_folder_path =
        util::Path::getRelativeToApp(".vscode", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // bin
    folder_path = util::PathStorage::getFolderPath("bin");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("bin", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // build
    folder_path = util::PathStorage::getFolderPath("build");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("build", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // app
    folder_path = util::PathStorage::getFolderPath("app");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // sources_main
    folder_path = util::PathStorage::getFolderPath("sources_main");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("sources_main", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // scripts
    folder_path = util::PathStorage::getFolderPath("scripts");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("scripts", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // sources
    folder_path = util::PathStorage::getFolderPath("sources");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("sources", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // resource
    folder_path = util::PathStorage::getFolderPath("resource");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("resource", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // devops
    folder_path = util::PathStorage::getFolderPath("devops");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("devops", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // sources_test
    folder_path = util::PathStorage::getFolderPath("sources_test");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("sources_test", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // config
    folder_path = util::PathStorage::getFolderPath("config");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("config", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // tests_legacy
    folder_path = util::PathStorage::getFolderPath("tests_legacy");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("tests_legacy", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // data
    folder_path = util::PathStorage::getFolderPath("data");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("data", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    //.git
    folder_path = util::PathStorage::getFolderPath(".git");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp(".git", true);

    EXPECT_EQ(folder_path, correct_folder_path);

    // sources_legacy
    folder_path = util::PathStorage::getFolderPath("sources_legacy");

    ASSERT_TRUE(folder_path.has_value());

    correct_folder_path = util::Path::getRelativeToApp("sources_legacy", true);

    EXPECT_EQ(folder_path, correct_folder_path);
}

// Difficult tests for PathStorageAddFolderPath and PathStorageGetFolderPath
//------------------------------------------------------------------------------

TEST(PathStorageAddAndGetFolderPath,
     test_add_folder_path_without_name_and_get_folder_path)
{
    std::string new_folder_path =
        util::Path::getRelativeToApp("someFolder1/SomeFolder2", true);

    util::PathStorage::addFolder(new_folder_path);

    auto folder_path = util::PathStorage::getFolderPath("SomeFolder2");

    ASSERT_TRUE(folder_path.has_value());

    EXPECT_EQ(folder_path, new_folder_path);
}

TEST(PathStorageAddAndGetFolderPath,
     test_add_folder_path_with_name_and_get_folder_path)
{
    std::string new_folder_path =
        util::Path::getRelativeToApp("someFolder1/SomeFolder2", true);
    std::string_view new_name = "SomeFolder2";
    util::PathStorage::addFolder(new_name, new_folder_path);

    auto folder_path = util::PathStorage::getFolderPath("SomeFolder2");

    ASSERT_TRUE(folder_path.has_value());

    EXPECT_EQ(folder_path, new_folder_path);
}

//------------------------------------------------------------------------------
// Simple tests for PathStorageGetFilePath
TEST(PathStorageGetFilePath, test_get_file_path_sources_legacy)
{
    auto folder_path = util::PathStorage::getFilePath("command.txt");

    ASSERT_TRUE(folder_path.has_value());

    std::string correct_folder_path =
        util::Path::getRelativeToApp("data", true) + "command.txt";

    EXPECT_EQ(folder_path, correct_folder_path);
}
//------------------------------------------------------------------------------
// Difficult tests for PathStorageAddFilePath and PathStorageGetFilePath
//------------------------------------------------------------------------------
TEST(PathStorageAddAndGetFilePath,
     test_add_file_path_without_name_and_get_file_path)
{
    std::string new_file_path =
        util::Path::getRelativeToApp("someFolder1/SomeFile", true);
    // std::string new_name        = ""
    util::PathStorage::addFile(new_file_path);

    auto file_path = util::PathStorage::getFilePath("SomeFile");

    ASSERT_TRUE(file_path.has_value());

    EXPECT_EQ(file_path, new_file_path);
}

TEST(PathStorageAddAndGetFilePath,
     test_add_file_path_with_name_and_get_file_path)
{
    std::string new_file_path =
        util::Path::getRelativeToApp("someFolder1/SomeFile", true);
    std::string_view new_name = "SomeFile";
    util::PathStorage::addFile(new_name, new_file_path);

    auto file_path = util::PathStorage::getFilePath("SomeFile");

    ASSERT_TRUE(file_path.has_value());

    EXPECT_EQ(file_path, new_file_path);
}
//------------------------------------------------------------------------------
// Simple tests for PathStorageCreateRemoveFolder
//------------------------------------------------------------------------------

bool
exists(const std::string_view& path)
{
    return std::filesystem::exists(std::filesystem::path(path));
}

TEST(PathStorageCreateAndRemoveFolder, test_add_remove_folder)
{
    DECLARE_LOCAL_CONTEXT;

    std::string main_folder = "mainFolder";

    std::array<std::string, 3> file_name_array   = {"file0, file1, file2"};
    std::array<std::string, 3> folder_name_array = {"folder0, file1, file2"};

    std::string main_folder_path =
        util::Path::getRelativeToApp(main_folder, true);

    /////////
    // create main folder with some files, check that path is correct

    ASSERT_TRUE(util::PathStorage::touchFolder(main_folder_path) ==
                util::PathStorage::getFolderPath(main_folder));

    for (int file_index = 0; file_index < 3; ++file_index)
    {
        ASSERT_TRUE(
            util::PathStorage::touchFolder(main_folder_path + "/" +
                                           file_name_array[file_index]) ==
            util::PathStorage::getFolderPath(file_name_array[file_index]));
    }

    // util::PathStorage::

    // check that main folder exists

    ASSERT_TRUE(exists(main_folder_path));

    // remove folder
    util::PathStorage::removeFolder(main_folder, LOCAL_CONTEXT);

    // check that main folder does not exist
    ASSERT_FALSE(exists(main_folder_path));
    ///////
}
//------------------------------------------------------------------------------
