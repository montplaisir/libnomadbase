
#include "Math/LHS.hpp"
#include "Math/RNG.hpp"

#include <algorithm>

// Constructor
NOMAD::LHS::LHS(int n, int p, int seed)
:   _n(n),
    _p(p),
    _l(),
    _u(),
    _seed(seed)
{
    std::srand(_seed);
}

// Copy constructor
NOMAD::LHS::LHS(const NOMAD::LHS &lhs)
:   _n(lhs._n),
    _p(lhs._p),
    _l(lhs._l),
    _u(lhs._u),
    _seed(lhs._seed)
{
}

// Destructor
NOMAD::LHS::~LHS(void)
{
}


// Do the sample
// Audet & Hare Algorithm 3.9 Latin Hypercube Sampling
std::vector<NOMAD::Point*> NOMAD::LHS::Sample() const
{
    std::vector<NOMAD::Point*> samplepoints;

    // 0 - Initialization
    // Let Pi be a n x p matrix in which each of its n rows
    // is a random permutation of the vector (1, 2, .., p).
    //
    std::vector<std::vector<int> > Pi;
    for (int i = 0; i < _n; i++)
    {
        std::vector<int> v = Permutation(_p);
        Pi.push_back(v);
    }

    // 1 - Sample construction
    for (int j = 0; j < _p; j++)
    {
        Point* point = new Point(_n);
        for (int i = 0; i < _n; i++)
        {
            NOMAD::Double r_ij = RNG::rand(0,1);
            // Convert ints to Doubles to ensure there is no hidden rounding
            NOMAD::Double l_i(_l[i]);
            NOMAD::Double Pi_ij( Pi[i][j] );
            NOMAD::Double pdouble( _p );
            NOMAD::Double u_i( _u[i] );

            /* VRM for debug
            cout << "VRM: x" << i << j << " = " << l_i;
            cout << " + (" << Pi_ij << " - " << r_ij << ")";
            cout << "/ " << _pdouble << " * (" << u_i << " - " << l_i << ")" << endl;
            */
            NOMAD::Double x_ij = l_i + (Pi_ij - r_ij) / pdouble * (u_i - l_i);
            (*point)[i] = x_ij;
        }
        samplepoints.push_back(point);
    }

    return samplepoints;
}

// Input: p
// Output: Random permutation of the vector (1, 2, .., p)
std::vector<int> NOMAD::LHS::Permutation(const int p)
{
    std::vector<int> v;
    for (int j = 1; j <= p; j++)
    {
        v.push_back(j);
    }

    std::random_shuffle(v.begin(), v.end());

    return v;
}
