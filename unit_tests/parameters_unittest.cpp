
// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include "Param/Parameters.hpp"
#include "Util/fileutils.hpp"
#include "gtest/gtest.h"

#include <iostream>
using namespace std;

// Step 2. Use the TEST macro to define your tests.

// Tests Parameters class.

// Basic tests for Parameters
TEST(ParametersTest, Basic) {
    // This test is named "Basic", and belongs to the "ParametersTest"
    // test case.

    Parameters all_parameters = Parameters();

    Param p1("first_parameter", 1.1);
    bool param1_added = all_parameters.add(p1);
    EXPECT_EQ(true, param1_added);

    Param p2("second_parameter", "string value");
    bool param2_added = all_parameters.add(p2);
    EXPECT_EQ(true, param2_added);

    Param p3("third_parameter", 3.3);
    bool param3_added = all_parameters.add(p3);
    EXPECT_EQ(true, param3_added);

    // Adding a parameter that is already there
    Param p4("third_parameter", 3.3);
    bool param4_added = all_parameters.add(p4);
    EXPECT_EQ(true, param4_added);

    // Adding a parameter that is already there, but with a new value
    Param p5("third_parameter", 3.5);
    bool param5_added = all_parameters.add(p5);
    EXPECT_EQ(true, param5_added);

    // Again
    Param p6("third_parameter", 3.1);
    bool param6_added = all_parameters.add(p6);
    EXPECT_EQ(true, param6_added);

    // Testing fileutils::curdir
    string testdir = NOMAD::curdir();
    cout << "VRM: testdir = " << testdir << endl;
    string unittestdir = "unit_tests";
    bool in_unit_tests_dir = (testdir.find(unittestdir) != std::string::npos);
    if (!in_unit_tests_dir)
    {
        testdir = testdir + NOMAD::DIR_SEP + unittestdir;
        cout << "VRM: testdir is now " << testdir << endl;
    }

    // Testing fileutils::dirname here
    string dir1 = NOMAD::dirname("mads_3.8.Dev.txt");
    EXPECT_EQ("./", dir1);
    string dir2 = NOMAD::dirname("/home/toto/path/directory/to/file.txt");
    EXPECT_EQ("/home/toto/path/directory/to/", dir2);

    // Testing fileutils::fullpath
    string full1 = NOMAD::fullpath("some_file.txt");
    EXPECT_EQ("./some_file.txt", full1);
    string full2 = NOMAD::fullpath("/home/toto/path/to/file2.txt");
    EXPECT_EQ("/home/toto/path/to/file2.txt", full2);

    // Testing fileutils::check_read_file
    string default_filename = "mads_3.8.Dev.txt";
    string full3 = NOMAD::fullpath(testdir + NOMAD::DIR_SEP + default_filename);
    bool file_is_readable = NOMAD::check_read_file(full3);
    EXPECT_EQ(true, file_is_readable);

    // Read parameters from the default file
    cout << "Read file " << full3 << endl;
    all_parameters.read_from_file(full3);

    string new_params_file = "mads_test1.txt";
    string full_new = NOMAD::fullpath(testdir + NOMAD::DIR_SEP + new_params_file);
    file_is_readable = NOMAD::check_read_file(full_new);
    EXPECT_EQ(true, file_is_readable);

    std::string param_name = "PARAM1";
    Param tp1(param_name, bool(0));
    bool param1_found = all_parameters.find(param_name, tp1);
    EXPECT_EQ(true, param1_found);
    // VRM: To think about: Value is 1. How should it be converted when read from the file?
    // Right now, it seems to always be a string.
    std::string tp1_s = tp1.get_value<std::string>();
    EXPECT_EQ(std::string("1"), tp1.get_value<std::string>());

    // Read parameters from the new file, they will be updated.
    cout << "Read file " << full_new << endl;
    all_parameters.read_from_file(full_new);

    // Value of PARAM1 should now be 100.100
    param1_found = all_parameters.find(param_name, tp1);
    EXPECT_EQ(true, param1_found);
    tp1_s = tp1.get_value<std::string>();
    EXPECT_EQ(std::string("100.100"), tp1.get_value<std::string>());

    // Output parameters to a file
    std::cout << std::endl << std::endl;
    try
    {
        all_parameters.write_to_file("test_write_param.txt");
    }
    catch ( std::exception & e )
    {
        cerr << "Exception thrown: " << e.what() << endl;
    }


}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
