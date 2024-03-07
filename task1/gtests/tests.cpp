#include <gtest/gtest.h>

#include "../build/version.h"

 TEST(TestVersion, test_valid_version) {
    EXPECT_TRUE(BUILD_VERSION>0);

}
