#include <libtech/mytime.h>
#include <stdio.h>

#include "gtest/gtest.h"

TEST(FactorialTest, Negative) {
    EXPECT_GT(get_a_ticks(), 0);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
