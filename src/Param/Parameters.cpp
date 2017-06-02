
#include <fstream>
#include <Util/fileutils.hpp>
#include <Util/utils.hpp>
#include "Parameters.hpp"

Parameters::Parameters()
  : m_params()
{
}

bool Parameters::add(const Param &p)
{
    ParamValue pv = p.get_paramvalue();
    std::pair<std::set<Param>::iterator,bool> ret;
    ret = m_params.insert(p);
    bool inserted = ret.second;
    if (!inserted)
    {
        // We will change the value of the parameter by erasing it,
        // and adding the new one.
        std::set<Param>::iterator it_oldparam = ret.first;
        m_params.erase(it_oldparam);
        ret = m_params.insert(p);
        inserted = ret.second;
    }
    return inserted;
}

bool Parameters::find(const std::string name, Param &foundparam) const
{
    const Param t_param(name, ParamValue(true));
    std::set<Param>::const_iterator it = m_params.find(t_param);
    const bool found = (it != m_params.end());
    if (found)
    {
        foundparam = (*it);
    }
    return found;
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
        // First space delimits the split between parameter name and value(s).
        // VRM for now, only 1 value is supported.
        size_t split_index = line.find(' ');
        if (split_index != std::string::npos)
        {
            std::string name = line.substr(0, split_index);
            std::string value_string = line.substr(split_index+1, line.size());
            // VRM value will all be strings for now, to review.
            // TODO convert to NOMAD::Double, etc.
            Param param(name, value_string);
            if (!this->add(param))
            {
                std::cerr << "Could not add parameter " << param.get_name() << std::endl;
                // VRM TODO add reasons
            }
        }

    }

    // Close file
    fin.close();

}

void Parameters::write_to_file(const std::string &filename) const
{
    // VRM: Not complete yet. TODO.
    std::cout << "VRM: Output to file " << filename << std::endl;
    std::cout << "VRM: Number of parameters: " << m_params.size() << std::endl;

    if (filename.empty())
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "File name is empty" );
    }

    debug_display();
    /*
    for (std::set<Param>::const_iterator it = m_params.begin(); it != m_params.end(); it++)
    {
        std::cout << it->get_name() << "\t" << it->get_paramvalue() << std::endl;
    }
    */

}

void Parameters::debug_display() const
{
    for (std::set<Param>::const_iterator it = m_params.begin(); it != m_params.end(); it++)
    {
        std::cout << it->get_name() << "\t" << it->get_paramvalue() << std::endl;
    }
}
