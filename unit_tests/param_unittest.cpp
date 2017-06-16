
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
    EXPECT_EQ(false,    NOMAD::Param::name_is_valid(s));
    s = "Name2";
    EXPECT_EQ(false,    NOMAD::Param::name_is_valid(s));
    s = "NAME3";
    EXPECT_EQ(true,     NOMAD::Param::name_is_valid(s));
    s = "NAME 4";
    EXPECT_EQ(false,    NOMAD::Param::name_is_valid(s));
    s = "NAME_5";
    EXPECT_EQ(true,     NOMAD::Param::name_is_valid(s));
    s = "NAME_6_IS4TESTING";
    EXPECT_EQ(true,     NOMAD::Param::name_is_valid(s));


    //Create a parameter with a valid name and value
    std::string name1 = "NAME1";
    NOMAD::ParamValue value1 = NOMAD::Double(1.111);
    NOMAD::Param p1(name1, value1);
    EXPECT_EQ(name1,  p1.get_name());
    EXPECT_EQ(value1, p1.get_value_double());

    //Create a parameter with an invalid name (fail)
    std::string name2 = "NAME 2";
    double value2 = 2.2;
    try
    {
        NOMAD::Param p2(name2, value2);
        FAIL(); // Fail... unless an exception is thrown.
    }
    catch( const NOMAD::Exception& err )
    {
        // VRM this str checking is too specific, but we will leave it like this for now.
        // If it becomes too combersome, just skip it.
        std::string expected = "NOMAD::Exception thrown (Param.cpp, 41) Param name \"" + name2 + "\" is not valid";
        EXPECT_EQ( expected, err.what() );
    }

    // Create a parameter with an invalid value (fail)
    std::string name3 = "NAME3";
    std::string type3 = "bool";
    std::string value3 = "2";
    try
    {
        NOMAD::Param p3(name3, value3, type3);
        FAIL(); // Fail... unless an exception is thrown.
    }
    catch( const NOMAD::Exception& err )
    {
        // VRM this str checking is too specific, but we will leave it like this for now.
        std::string expected = "NOMAD::Exception thrown (Param.cpp, 46) Param value \"" + value3 + "\" is not valid for type " + type3;
        EXPECT_EQ( expected, err.what() );
    }

    std::string name4 = "NAME_4";
    double value4     = 4.4;
    NOMAD::Param p4(name4, value4);
    EXPECT_EQ(name4,  p4.get_name());
    EXPECT_EQ(NOMAD::Double(value4), p4.get_value_double());

    std::string name5 = "NAME_5";
    bool value5       = true;
    NOMAD::Param p5(name5, value5);
    EXPECT_EQ(name5,  p5.get_name());
    EXPECT_EQ(value5, p5.get_value_bool());

    std::string name6    = "NAME_6";
    NOMAD::Double value6 = 6.6;
    NOMAD::Param p6(name6, value6);
    EXPECT_EQ(name6,  p6.get_name());
    EXPECT_EQ(value6, p6.get_value_double());

    // Create a value of invalid type
    std::string name8     = "NAME_8";
    std::string value8    = "foo";
    std::string type_str8 = "NOMAD::Double";
    try
    {
        NOMAD::Param p8(name8, value8, type_str8);
    }
    catch (const NOMAD::Exception &err8)
    {
        std::string expected8 = "NOMAD::Exception thrown (Param.cpp, 46) Param value \"" + value8 + "\" is not valid for type NOMAD::Double";
        EXPECT_EQ( expected8, err8.what() );
    }

    // Try to change a const parameter value (fail)
    std::string name9 = "NAME_9";
    NOMAD::Double value9(9.9);
    bool value9_is_const = true;
    NOMAD::Param p9(name9, value9, "TOTO", value9_is_const);
    try
    {
        p9.set_value(0.99999);
        FAIL();
    }
    catch ( const NOMAD::Exception& err )
    {
        EXPECT_STREQ( "NOMAD::Exception thrown (Param.cpp, 131) Param value is const and cannot be modified", err.what() );
    }
    EXPECT_EQ(name9,  p9.get_name());
    EXPECT_EQ(value9, p9.get_value_double());

    // Try to change a non-const parameter value (success) - should be 0.12345
    std::string name10 = "NAME_10";
    NOMAD::ParamValue value10(10.101);
    bool value10_is_const = false;
    NOMAD::Param p10(name10, value10, "TOTO", value10_is_const);
    EXPECT_EQ(name10,  p10.get_name());
    EXPECT_EQ(value10, p10.get_value_double());
    p10.set_value(0.12345);
    EXPECT_EQ(name10,  p10.get_name());
    EXPECT_EQ(0.12345, p10.get_value_double());

    // Try to set value to a double - should be 0.2468"
    std::string name11 = "NAME_11";
    NOMAD::Double value11 = 0.2468;
    NOMAD::Param p11(name11, value11);
    EXPECT_EQ(name11,  p11.get_name());
    EXPECT_EQ(value11, p11.get_value_double());

    // Verify name is converted to caps
    std::string name12 = "Name_12";
    double value12 = 0;
    NOMAD::Param p12(name12, value12);
    EXPECT_EQ("NAME_12", p12.get_name());

    // Verify string parameter value is correctly added
    std::string name13 = "NAME_13";
    std::string value13 = "String value for name 13";
    NOMAD::Param p13(name13, value13);
    EXPECT_EQ(value13, p13.get_value_str());

    // Verify char* parameter value is correctly added
    std::string name14 = "NAME_14";
    const char* value14 = "char* value 14";
    NOMAD::Param p14(name14, value14);
    EXPECT_EQ(std::string(value14), p14.get_value_str());
}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
