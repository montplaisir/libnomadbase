
// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include "Math/Double.hpp"
#include "gtest/gtest.h"


// Step 2. Use the TEST macro to define your tests.

// Tests Double class.

// Basic tests for Double
TEST(DoubleTest, Basic) {
    // This test is named "Basic", and belongs to the "DoubleTest"
    // test case.

    NOMAD::Double d;
    double pi = 3.14159265358979323;
    d = pi;
    EXPECT_EQ(pi, d);

}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
