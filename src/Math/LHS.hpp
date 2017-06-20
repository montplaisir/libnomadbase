
// Latin Hypercube Sampling class.
//
// Input: 
// n dimension
// l and u vectors of R^n indicating lower and upper bounds
// p number of desired samples
// seed (optional)
//
// Output:
// p points of dimension n, distributed in the l x u hyper-rectangle of R^n
#ifndef __NOMAD400_LHS__
#define __NOMAD400_LHS__

#include <vector>
#include "Math/Double.hpp"
#include "Math/Point.hpp"
using namespace std;

#include "nomad_nsbegin.hpp"

class LHS
{
private:
    int _n;
    int _p;
    std::vector<int> _l;
    std::vector<int> _u;
    int _seed;

public:
    // Constructor
    explicit LHS(int n = 1, int p = 1, int seed = 2920);

    // Copy constructor
    LHS(const LHS& lhs);

    // Destructor
    // VRM if this class becomes a base class, then the destructor
    // needs to be virtual. But this is not the case currently.
    // See Effective C++ Item 7.
    ~LHS(void); 

    // Get/Set seed for random generation
    int     get_seed(void) const     { return _seed; }
    void    set_seed(const int seed) { _seed = seed; }

    // Get/Set lower and upper limits
    std::vector<int>    get_l(void) const     { return _l; }
    void    set_l(const std::vector<int> l)   { _l = l;    }
    std::vector<int>    get_u(void) const     { return _u; }
    void    set_u(const std::vector<int> u)   { _u = u;    }

    // Do the sampling
    std::vector<NOMAD::Point*> Sample() const;

    // Input: p
    // Output: Random permutation of the vector (1, 2, .., p)
    static std::vector<int> Permutation(const int p);
};

#include "nomad_nsend.hpp"

#endif
