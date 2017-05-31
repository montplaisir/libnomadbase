
#include <fstream>
#include <Util/fileutils.hpp>
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
    if (filename.empty())
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "File name is empty" );
    }

    std::string full_filename = NOMAD::fullpath(filename);
    std::ifstream fin;
    std::string err = "Could not open parameters file " + full_filename;

    if (NOMAD::check_read_file (full_filename))
    {
        fin.open( full_filename.c_str() );

        if (fin.fail())
        {
            fin.close();
            throw NOMAD::Exception(__FILE__, __LINE__, err);
        }
        else
        {
            err.clear();
        }
    }

    std::string line;
    while (fin.good() && !fin.eof())
    {
        getline(fin, line);
        // Remove comments
        NOMAD::remove_comments(line);
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
