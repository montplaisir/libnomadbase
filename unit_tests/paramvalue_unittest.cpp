
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
    NOMAD::ParamValue value1(d1);
    NOMAD::Double d1_get1 = value1.get_value_double();
    double d1_get = d1_get1.todouble();
    EXPECT_EQ(d1, d1_get);

    // NOMAD::Double value
    NOMAD::Double d2 = 5471;
    NOMAD::ParamValue value2(d2);
    NOMAD::Double d2_get = value2.get_value_double();
    EXPECT_EQ(d2, d2_get);

    // bool value
    bool b3 = 1;
    NOMAD::ParamValue value3(b3);
    bool b3_get = value3.get_value_bool();
    EXPECT_EQ(b3, b3_get);

    // string value
    std::string s4 = "5471";
    NOMAD::ParamValue value4(s4);
    std::string s4_get = value4.get_value_str();
    EXPECT_EQ(s4, s4_get);

    // char* value
    const char* s5 = "10.101";
    NOMAD::ParamValue value5(s5);
    std::string s5_get1 = value5.get_value_str();
    const char* s5_get = s5_get1.c_str();
    EXPECT_STREQ(s5, s5_get);

    // int value
    int i6 = 12;
    NOMAD::ParamValue value6(i6);
    int i6_get = value6.get_value_int();
    EXPECT_EQ(i6, i6_get);

    // Test 0. A value of 0 is ambiguous because the type could be
    // a NOMAD::Double, bool, int, etc.
    // With the newer implementation of ParamValue, it compiles, but type is not well defined.
    NOMAD::ParamValue value7(0);
    //std::string t7_get = value7.get_type_str();

    // Test get string value at index
    std::string s8 = "index0 First secondsecond Third 4th 55555 sixth";
    NOMAD::ParamValue value8(s8);
    std::string s8_get0 = value8.get_value_str(0);
    std::string s8_get1 = value8.get_value_str(1);
    std::string s8_get2 = value8.get_value_str(2);
    std::string s8_get3 = value8.get_value_str(3);
    std::string s8_get4 = value8.get_value_str(4);
    std::string s8_get5 = value8.get_value_str(5);
    std::string s8_get6 = value8.get_value_str(6);
    EXPECT_EQ("index0", s8_get0);
    EXPECT_EQ("First",  s8_get1);
    EXPECT_EQ("secondsecond", s8_get2);
    EXPECT_EQ("Third",  s8_get3);
    EXPECT_EQ("4th",    s8_get4);
    EXPECT_EQ("55555",  s8_get5);
    EXPECT_EQ("sixth",  s8_get6);
    // Will print a warning to cerr.
    std::string s8_get7 = value8.get_value_str(7);

    // A NOMAD::Double is valid even if it is not defined.
    std::string s9 = NOMAD::DEFAULT_UNDEF_STR; // "NaN"
    NOMAD::ParamValue value9("NOMAD::Double", s9);
    NOMAD::Double d9_get = value9.get_value_double();
    EXPECT_EQ(false, d9_get.is_defined());
    EXPECT_EQ(NOMAD::DEFAULT_UNDEF_STR, d9_get.tostring());
    std::string s9_get = value9.get_value_str();
    EXPECT_EQ(NOMAD::DEFAULT_UNDEF_STR, s9_get);

}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.

