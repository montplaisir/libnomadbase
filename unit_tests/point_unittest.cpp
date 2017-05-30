
// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include "Math/Point.hpp"
#include "gtest/gtest.h"


// Step 2. Use the TEST macro to define your tests.

// Tests Point class.

// Basic tests for Point
TEST(PointTest, Basic) {
    // This test is named "Basic", and belongs to the "PointTest"
    // test case.

    // Set a point and an f value
    // p has dimension 3 and p = (3.1, 3.1, 3.1)
    NOMAD::Double def_val = 3.1;
    NOMAD::Point p(3, def_val);

    EXPECT_EQ(p.get_size(), 3);

    EXPECT_EQ(p[0], 3.1);
    EXPECT_EQ(p[1], 3.1);
    EXPECT_EQ(p[2], 3.1);

    p[1] = 4.1;
    EXPECT_EQ(p[1], 4.1);
    // Now p = (3.1, 4.1, 3.1)

    // Test copy constructor
    NOMAD::Point p2(p);
    EXPECT_TRUE(p == p2);
    EXPECT_EQ(p2[0], 3.1);
    EXPECT_EQ(p2[1], 4.1);
    EXPECT_EQ(p2[2], 3.1);

}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
