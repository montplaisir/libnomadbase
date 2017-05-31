
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
    bool inserted = all_parameters.add(p1);
    cout << "Param inserted: " << inserted << endl;

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
    string filename = "mads_3.8.Dev.txt";
    string full3 = NOMAD::fullpath(testdir + NOMAD::DIR_SEP + filename);
    bool file_is_readable = NOMAD::check_read_file(full3);
    EXPECT_EQ(true, file_is_readable);

    // Read parameters from a file
    cout << "Read file " << full3 << endl;
    all_parameters.read_from_file(full3);
    //cerr << "Exception thrown: " << e.what() << endl;

/*
    // Output parameters to a file
    try
    {
        all_parameters.write_to_file("");
    }
    catch ( std::exception & e )
    {
        cerr << "Exception thrown: " << e.what() << endl;
    }
*/


}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
