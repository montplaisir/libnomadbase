
// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include "Math/Vector.hpp"
#include "gtest/gtest.h"

// Step 2. Use the TEST macro to define your tests.

// Tests Vector class.

// Basic tests for Vector
TEST(VectorTest, Basic) {
    // This test is named "Basic", and belongs to the "VectorTest"
    // test case.

    // Test constructors
    NOMAD::Point p1(4);
    p1[0] = 1.1;
    p1[1] = 2.3;
    p1[2] = 4.2;
    p1[3] = 3.1;
    NOMAD::Point p2(4);
    p2[0] = 2.1;
    p2[1] = 2.4;
    p2[2] = 4.1;
    p2[3] = 1.1;
    NOMAD::Point p3(3);
    p3[0] = 2.5;
    p3[1] = 2.3;
    p3[2] = 4.2;

    // Constructor using 2 points
    NOMAD::Vector v1(p1, p2);
    // Constructor using 1 point
    NOMAD::Vector v2(p3);
    // Degenerate vector
    NOMAD::Vector v3(p1, p1);
    // Inverse vector from v1
    NOMAD::Vector v1i(p2,p1);

    // Test norm
    double n1 = sqrt( pow(2.1-1.1,2) + pow(2.4-2.3,2) + pow(4.1-4.2,2) + pow(1.1-3.1,2) );
    double n2 = sqrt(2.5*2.5+2.3*2.3+4.2*4.2);
    EXPECT_EQ(n1, v1.norm());
    EXPECT_EQ(n2, v2.norm());
    EXPECT_EQ(0,  v3.norm());
    EXPECT_EQ(n1, v1i.norm());

}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
