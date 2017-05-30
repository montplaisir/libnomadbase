
// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include "Param/ParamValue.hpp"
#include "Math/Double.hpp"
#include "gtest/gtest.h"


// Step 2. Use the TEST macro to define your tests.

// Tests ParamValue class.

// Basic tests for ParamValue
TEST(ParamValueTest, Basic) {
    // This test is named "Basic", and belongs to the "ParamValueTest"
    // test case.

    // double value
    double d1 = 10.101;
    ParamValue value1(d1);
    ValueVariant v1 = value1.get_value();
    NOMAD::Double d1_get1 = boost::get<NOMAD::Double>(v1);
    double d1_get2 = d1_get1.todouble();
    EXPECT_EQ(d1, d1_get2);

    // NOMAD::Double value
    NOMAD::Double d2 = 5471;
    ParamValue value2(d2);
    ValueVariant v2 = value2.get_value();
    NOMAD::Double d2_get = boost::get<NOMAD::Double>(v2);
    EXPECT_EQ(d2, d2_get);

    // bool value
    bool d3 = 1;
    ParamValue value3(d3);
    ValueVariant v3 = value3.get_value();
    bool d3_get = boost::get<bool>(v3);
    EXPECT_EQ(d3, d3_get);
}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.

