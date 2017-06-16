// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include "Math/LHS.hpp"
#include "Math/Point.hpp"
#include "Math/RNG.hpp"

#include "gtest/gtest.h"

// Step 2. Use the TEST macro to define your tests.

// Tests Latin Hypercube Sample (LHS) class.

// Basic tests
TEST(LHSTest, Basic) {
    // This test is named "Basic", and belongs to the "LHSTest"
    // test case.

    // Create LHS for n = 2 (dimension of the points), p = 5 (number of samples)
    const int n = 10;
    const int p = 5;
    NOMAD::LHS *lhs = new NOMAD::LHS(n, p);

    // Set lower and upper limits
    std::vector<int> l;
    std::vector<int> u;

    NOMAD::RNG::set_seed(375);
    for (int i = 0; i < n; i++)
    {
        int li = floor(NOMAD::RNG::rand(0,1000));
        int ui = ceil(NOMAD::RNG::rand(0,1000));
        if (li > ui) { int t = li; li = ui; ui = t; } // swap
        l.push_back(li);
        u.push_back(ui);
    }
    // Ensure we have n elements
    EXPECT_EQ(l.size(), n);
    EXPECT_EQ(u.size(), n);
    lhs->set_l(l);
    lhs->set_u(u);
    
    // Verify limits are correctly set + verify get/set
    std::vector<int> test_l = lhs->get_l();
    std::vector<int> test_u = lhs->get_u();
    EXPECT_EQ(l.size(), test_l.size());
    EXPECT_EQ(u.size(), test_u.size());
    for (int i = 0; i < n; i++)
    {
        EXPECT_EQ(l[i], test_l[i]);
        EXPECT_EQ(u[i], test_u[i]);
    }
    
    // Run the Permutation algorithm
    std::vector<int> permutation = NOMAD::LHS::Permutation(p);

    // Run the sampling algorithm
    // Expecting p samples
    std::vector<NOMAD::Point*> sample = lhs->Sample();
    EXPECT_EQ(p, sample.size());

    // Verify points satisfy lower and upper bounds
    for (int j = 0; j < p; j++)
    {
        NOMAD::Point *point = sample[j];
        for (int i = 0; i < n; i++)
        {
            EXPECT_GE((*point)[i], l[i]);
            EXPECT_LE((*point)[i], u[i]);
        }
    }

    // Delete LHS
    delete lhs;
}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
