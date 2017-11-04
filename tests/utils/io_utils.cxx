#include <gtest/gtest.h>

#include <ogf/utils/io_utils.hxx>

TEST(io_utils, get_file_extension) {
    const auto input = "/home/user/some/funny/path/some-funny-filename.ext";
    const auto result = ogf::get_file_extension(input);
    ASSERT_EQ(result, "ext");
}
