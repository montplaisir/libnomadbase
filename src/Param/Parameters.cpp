
#include <fstream>
#include <Util/utils.hpp>
#include "Parameters.hpp"

Parameters::Parameters()
  : _params()
{
}

bool Parameters::add(const Param &p)
{
    std::pair<std::set<Param>::iterator,bool> ret;
    ret = _params.insert(p);
    return ret.second;
}

void Parameters::read_from_file(const std::string &filename)
{
    std::cout << "Reading from file " << filename << std::endl;

    if (filename.empty())
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "File name is empty" );
    }

    std::string complete_filename = "./" + filename;
    std::ifstream fin ( complete_filename.c_str() ); // VRM: Make this better, see for ex. NOMAD_3 Parameters.
    std::string err = "Could not open parameters file " + complete_filename;

    //if (NOMAD::check_read_file (filename)) // VRM: copied... merge with NOMAD_3.
        // TODO: Add check_read_file...
    {
        fin.open( complete_filename.c_str() );
        if (!fin.fail() )
        {
            err.clear();
        }
        if (!err.empty())
        {
            fin.close();
            throw NOMAD::Exception(__FILE__, __LINE__, err);
        }
    }

    // Close file
    fin.close();
}

void Parameters::write_to_file(const std::string &filename)
{
    std::cout << "Output to file " << filename << std::endl;

    if (filename.empty())
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "File name is empty" );
    }
}
