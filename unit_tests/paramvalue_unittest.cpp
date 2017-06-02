
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
    NOMAD::Double v1 = value1.get_value<NOMAD::Double>();
    double d1_get2 = v1.todouble();
    EXPECT_EQ(d1, d1_get2);

    // NOMAD::Double value
    NOMAD::Double d2 = 5471;
    ParamValue value2(d2);
    ValueVariant v2 = value2.get_value<NOMAD::Double>();
    NOMAD::Double d2_get = boost::get<NOMAD::Double>(v2);
    EXPECT_EQ(d2, d2_get);

    // bool value
    bool d3 = 1;
    ParamValue value3(d3);
    ValueVariant v3 = value3.get_value<bool>();
    bool d3_get = boost::get<bool>(v3);
    EXPECT_EQ(d3, d3_get);

    // string value
    std::string s4 = "5471";
    ParamValue value4(s4);
    ValueVariant v4 = value4.get_value<std::string>();
    std::string s4_get = boost::get<std::string>(v4);
    EXPECT_EQ(s4, s4_get);

    // char* value
    const char* s5 = "10.101";
    ParamValue value5(s5);
    ValueVariant v5 = value5.get_value<std::string>();
    std::string s5_get1 = boost::get<std::string>(v5);
    const char* s5_get2 = s5_get1.c_str();
    EXPECT_STREQ(s5, s5_get2);

    // Test 0 - compilation only. This does not compile because 0 is ambiguous.
    // The 0 has to be converted to bool or NOMAD::Double beforehand.
    //ParamValue value6(0);
}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.

