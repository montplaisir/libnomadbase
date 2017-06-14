
// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include "Param/Parameters.hpp"
#include "Util/fileutils.hpp"
#include "gtest/gtest.h"


// Step 2. Use the TEST macro to define your tests.

// Tests Parameters class.

// Basic tests for Parameters
TEST(ParametersTest, Basic) {
    // This test is named "Basic", and belongs to the "ParametersTest"
    // test case.

    NOMAD::Parameters all_parameters = NOMAD::Parameters();

    NOMAD::Param p1("first_parameter", 1.1);
    bool param1_added = all_parameters.add(p1);
    EXPECT_EQ(true, param1_added);

    NOMAD::Param p2("second_parameter", "string value");
    bool param2_added = all_parameters.add(p2);
    EXPECT_EQ(true, param2_added);

    NOMAD::Param p3("third_parameter", 3.3);
    bool param3_added = all_parameters.add(p3);
    EXPECT_EQ(true, param3_added);

    // Adding a parameter that is already there
    NOMAD::Param p4("third_parameter", 3.3);
    bool param4_added = all_parameters.add(p4);
    EXPECT_EQ(true, param4_added);

    // Adding a parameter that is already there, but with a new value
    NOMAD::Param p5("third_parameter", 3.5);
    bool param5_added = all_parameters.add(p5);
    EXPECT_EQ(true, param5_added);

    // Again
    NOMAD::Param p6("third_parameter", 3.1);
    bool param6_added = all_parameters.add(p6);
    EXPECT_EQ(true, param6_added);

    // Testing fileutils::curdir
    std::string testdir = NOMAD::curdir();
    std::cout << "VRM: testdir = " << testdir << std::endl;
    std::string unittestdir = "unit_tests";
    bool in_unit_tests_dir = (testdir.find(unittestdir) != std::string::npos);
    if (!in_unit_tests_dir)
    {
        testdir = testdir + NOMAD::DIR_SEP + unittestdir;
        std::cout << "VRM: testdir is now " << testdir << std::endl;
    }

    // Testing fileutils::dirname here
    std::string dir1 = NOMAD::dirname("mads_3.8.Dev.txt");
    EXPECT_EQ("./", dir1);
    std::string dir2 = NOMAD::dirname("/home/toto/path/directory/to/file.txt");
    EXPECT_EQ("/home/toto/path/directory/to/", dir2);

    // Testing fileutils::fullpath
    std::string full1 = NOMAD::fullpath("some_file.txt");
    EXPECT_EQ("./some_file.txt", full1);
    std::string full2 = NOMAD::fullpath("/home/toto/path/to/file2.txt");
    EXPECT_EQ("/home/toto/path/to/file2.txt", full2);

    // Testing fileutils::check_read_file
    std::string runner_params_filename = "mads_3.8.Dev.txt";
    std::string full3 = NOMAD::fullpath(testdir + NOMAD::DIR_SEP + runner_params_filename);
    bool file_is_readable = NOMAD::check_read_file(full3);
    EXPECT_EQ(true, file_is_readable);

    // Read parameters from the runner parameters file
    std::cout << "VRM: Read file " << full3 << std::endl;
    all_parameters.read_from_file(full3);
    std::cout << "VRM: File read: " << full3 << std::endl;

    // Verify value of PARAM1. Should be "1".
    std::string param_name = "PARAM1";
    bool param1_found = all_parameters.is_defined(param_name);
    EXPECT_EQ(true, param1_found);
    std::string param1_s = all_parameters.get_value_str(param_name);
    EXPECT_EQ("1", param1_s);

    // Read parameters from the new file, they will be updated.
    std::string new_params_file = "mads_test1.txt";
    std::string full_new = NOMAD::fullpath(testdir + NOMAD::DIR_SEP + new_params_file);
    file_is_readable = NOMAD::check_read_file(full_new);
    EXPECT_EQ(true, file_is_readable);
    std::cout << "Read file " << full_new << std::endl;
    all_parameters.read_from_file(full_new);

    // Value of PARAM1 should now be "100.100".
    param1_found = all_parameters.is_defined(param_name);
    EXPECT_EQ(true, param1_found);
    std::string param2_s = all_parameters.get_value_str(param_name);
    EXPECT_EQ("100.100", param2_s);

    // Remove parameter
    bool b1 = all_parameters.remove(param_name);
    EXPECT_EQ(true, b1);
    param1_found = all_parameters.is_defined(param_name);
    EXPECT_EQ(false, param1_found);

    // Verify parameter "Second_Parameter" is found even if it
    // was entered as "second_parameter" and is stored as "SECOND_PARAMETER".
    bool param2_found = all_parameters.is_defined("Second_Parameter");
    EXPECT_EQ(true, param2_found);

    // Test update.
    // Ensure parameters that are set as const cannot be modified,
    // and that other parameters can be updated.
    // Should work because DISPLAY_DEGREE is an ALGO parameter.
    int i_updated1 = all_parameters.update("DISPLAY_DEGREE", "42");
    EXPECT_EQ(1, i_updated1);
    // Should not work because DIMENSION is a PROBLEM parameter.
    int i_updated2 = all_parameters.update("DIMENSION", "42");
    EXPECT_EQ(0, i_updated2);
    // Should not work because DIDI is not defined.
    int i_updated3 = all_parameters.update("DIDI", "42");
    EXPECT_EQ(-1, i_updated3);

    // Test getting values and types
    std::string s10 = all_parameters.get_value_str("SECOND_PARAMETER");
    std::string t_s10 = all_parameters.get_type_str("SECOND_PARAMETER");
    EXPECT_EQ("string value", s10);
    EXPECT_EQ("std::string", t_s10);

    NOMAD::Double d10 = all_parameters.get_value_double("MESH_UPDATE_BASIS");
    std::string t_d10 = all_parameters.get_type_str("MESH_UPDATE_BASIS");
    EXPECT_EQ(4, d10);
    EXPECT_EQ("NOMAD::Double", t_d10);

    bool b10 = all_parameters.get_value_bool("MODEL_PROJ_TO_MESH");
    std::string t_b10 = all_parameters.get_type_str("MODEL_PROJ_TO_MESH");
    EXPECT_EQ(true,b10);
    EXPECT_EQ("bool", t_b10);

    int i10 = all_parameters.get_value_int("USER_PARAM");
    std::string t_i10 = all_parameters.get_type_str("USER_PARAM");
    EXPECT_EQ(42,i10);
    EXPECT_EQ("int", t_i10);

    // Test find
    std::string param_name11 = "MODEL_MAX_Y_SIZE";
    int i11 = 55;   // bogus value only for param creation
    NOMAD::Param param(param_name11, i11);
    bool b11_found = all_parameters.find(param_name11, param);
    EXPECT_EQ(true, b11_found);
    int i11_val = param.get_value_int();
    EXPECT_EQ(500, i11_val);

    // Output parameters to a file
    std::cout << std::endl << std::endl;
    try
    {
        all_parameters.write_to_file("test_write_param.txt");
    }
    catch ( std::exception & e )
    {
        std::cerr << "Exception thrown: " << e.what() << std::endl;
    }


}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
