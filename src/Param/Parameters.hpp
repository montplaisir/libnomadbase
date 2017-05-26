
#ifndef __RUNNER400_PARAMETERS__
#define __RUNNER400_PARAMETERS__

#include <set>
#include "Param.hpp"

// Manage all parameters.
class Parameters
{
private:
    std::set<Param> _params;
public:
    explicit Parameters();
    virtual ~Parameters() {}

    // Add a Param to the list.
    // True if p was correctly added.
    bool add(const Param &p);

    // Read parameters from a file and insert them
    void read_from_file(const std::string &filename);

    // Output parameters to a file
    void write_to_file(const std::string &filename);
};



#endif
