#include <libtech/pathutils.h>

#include "gtest/gtest.h"

const char* test_case = "/root/folder/test.txt";
const char* invalid_slashes = "\\root\\folder\\test.txt";

TEST(PathTest, GetFileName)
{
    EXPECT_STREQ(get_file_name(test_case), "test.txt");
}

TEST(PathTest, GetFileNameNoExt)
{
    EXPECT_STREQ(get_file_name_noext(test_case), "test");
}

TEST(PathTest, GetFileExtension)
{
    EXPECT_STREQ(get_file_extension(test_case), ".txt");
}

TEST(PathTest, GetParentDirectoryPath)
{
    EXPECT_STREQ(get_parent_directory_path(test_case), "/root/folder");
}

TEST(PathTest, GetPathParts)
{
    std::list<char*>* parts = get_path_parts(test_case);

    auto data = parts->begin();

    char* part_1 = *data;
    char* part_2 = *(++data);
    char* part_3 = *(++data);

    EXPECT_STREQ(part_1, "root");
    EXPECT_STREQ(part_2, "folder");
    EXPECT_STREQ(part_3, "test.txt");
}

TEST(PathTest, SanitizePathSlashes)
{
    char ret_buf[128];
    sanitize_path_slashes(invalid_slashes, ret_buf);

    // Sanitized was converted OK.
    EXPECT_STREQ(ret_buf, test_case);

    // Sanitized is not equal to original
    EXPECT_STRNE(invalid_slashes, ret_buf);
}