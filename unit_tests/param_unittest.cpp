
// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include "Param/Param.hpp"
#include "gtest/gtest.h"


// Step 2. Use the TEST macro to define your tests.

// Tests Param class.

// Basic tests for Param
TEST(ParamTest, Basic) {
    // This test is named "Basic", and belongs to the "ParamTest"
    // test case.

    // Test name validity
    // A valid name is of the form:
    // Capital letter, followed by a combination of capital letters, numbers
    // and underscores, and ending by a capital letter or a number.
    std::string s("NAME1_");
    EXPECT_EQ(false, Param::name_is_valid(s));
    s = "Name2";
    EXPECT_EQ(false, Param::name_is_valid(s));
    s = "NAME3";
    EXPECT_EQ(true, Param::name_is_valid(s));
    s = "NAME 4";
    EXPECT_EQ(false, Param::name_is_valid(s));
    s = "NAME_5";
    EXPECT_EQ(true, Param::name_is_valid(s));
    s = "NAME_6_IS4TESTING";
    EXPECT_EQ(true, Param::name_is_valid(s));



    //Create a parameter with a valid name and value
    std::string name1 = "NAME1";
    ParamValue value1 = NOMAD::Double(1.111);
    Param p1(name1, value1);
    EXPECT_EQ(name1,  p1.get_name());
    EXPECT_EQ(value1, p1.get_value());

    //Create a parameter with an invalid name (fail)
    std::string name2 = "NAME 2";
    double value2 = 2.2;
    try
    {
        Param p2(name2, value2);
        FAIL(); // Fail... unless an exception is thrown.
    }
    catch( const NOMAD::Exception& err )
    {
        // VRM this str checking is too specific, but we will leave it like this for now.
        EXPECT_STREQ( "NOMAD::Exception thrown (Param.cpp, 25) Param name is not valid", err.what() );
    }

    // Create a parameter with an invalid value (fail)
    std::string name3 = "NAME3";
    NOMAD::Double value3 = NOMAD::Double();
    try
    {
        Param p3(name3, value3);
        FAIL(); // Fail... unless an exception is thrown.
    }
    catch( const NOMAD::Exception& err )
    {
        // VRM this str checking is too specific, but we will leave it like this for now.
        EXPECT_STREQ( "NOMAD::Exception thrown (Param.cpp, 29) Param value is not valid", err.what() );
    }

    std::string name4 = "NAME_4";
    double value4 = 4.4;
    Param p4(name4, value4);
    EXPECT_EQ(name4,  p4.get_name());
    EXPECT_EQ(ParamValue(value4), p4.get_value());

    std::string name5 = "NAME_5";
    bool value5 = true;
    Param p5(name5, value5);
    EXPECT_EQ(name5,  p5.get_name());
    EXPECT_EQ(ParamValue(value5), p5.get_value());

    std::string name6 = "NAME_6";
    NOMAD::Double value6 = 6.6;
    Param p6(name6, value6);
    EXPECT_EQ(name6,  p6.get_name());
    EXPECT_EQ(ParamValue(value6), p6.get_value());

    // Create a value of invalid type (fail at compile time)
    std::string name8 = "NAME_8";
    std::string value8("foo");
    //Param p8(name8, value8); // Compilation error

    // Try to change a const parameter value (fail)
    std::string name9 = "NAME_9";
    NOMAD::Double value9(9.9);
    bool value9_is_const = true;
    Param p9(name9, value9, "TOTO", value9_is_const);
    try
    {
        p9.set_value(0.99999);
    }
    catch ( const NOMAD::Exception& err )
    {
        EXPECT_STREQ( "NOMAD::Exception thrown (Param.cpp, 56) Param value is const and cannot be modified", err.what() );
    }
    EXPECT_EQ(name9,  p9.get_name());
    EXPECT_EQ(ParamValue(value9), p9.get_value());

    // Try to change a non-const parameter value (success) - should be 0.12345
    std::string name10 = "NAME_10";
    ParamValue value10(10.101);
    bool value10_is_const = false;
    Param p10(name10, value10, "TOTO", value10_is_const);
    EXPECT_EQ(name10,  p10.get_name());
    EXPECT_EQ(ParamValue(value10), p10.get_value());
    p10.set_value(0.12345);
    EXPECT_EQ(name10,  p10.get_name());
    EXPECT_EQ(ParamValue(0.12345), p10.get_value());

    // Try to set value to a double - should be 0.2468"
    std::string name11 = "NAME_11";
    NOMAD::Double value11 = 0.2468;
    Param p11(name11, value11);
    EXPECT_EQ(name11,  p11.get_name());
    EXPECT_EQ(ParamValue(value11), p11.get_value());
    EXPECT_EQ(ParamValue(0.2468), p11.get_value());

    // Verify name is converted to caps
    std::string name12 = "Name_12";
    double value12 = 0;
    Param p12(name12, value12);
    EXPECT_EQ("NAME_12", p12.get_name());
}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
