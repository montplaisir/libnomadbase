
// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include "Param/Parameters.hpp"
#include "gtest/gtest.h"


// Step 2. Use the TEST macro to define your tests.

// Tests Parameters class.

// Basic tests for Parameters
TEST(ParametersTest, Basic) {
    // This test is named "Basic", and belongs to the "ParametersTest"
    // test case.

    Parameters all_parameters = Parameters();
    Param p1("first_parameter", 1.1);
    bool inserted = all_parameters.add(p1);
    //cout << "Param inserted: " << inserted << endl;

    // Read parameters from a file
    //all_parameters.read_from_file("mads_3.8.Dev.txt");
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
