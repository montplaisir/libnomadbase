
#include <algorithm>
#include <fstream>
#include <Util/fileutils.hpp>
#include <Util/utils.hpp>
#include "Parameters.hpp"

// Initialize parameter categories static member.
std::string categories[] = {"ALGO", "PROBLEM", "RUNNER", "USER"};
const std::vector<std::string> NOMAD::Parameters::m_param_categories(categories, categories + sizeof(categories) / sizeof (std::string));

NOMAD::Parameters::Parameters()
  : m_params()
{
    // Initialize parameters to default values
    //
    // Hack to get to read the default parameters.
    std::istringstream default_params_stream(
#include "default_parameters.txt"
    );

    std::string line;
    while (default_params_stream.good() && !default_params_stream.eof())
    {
        getline(default_params_stream, line);

        parse_line(line);
    }
}

// Add the parameter.
// If a parameter with this name already exists, set its value
// to the input parameter's value.
// VRM TODO: If the parameter already exists, check category and type.
// If they mismatch with the input, return false. (to be detailed)
bool NOMAD::Parameters::add(const NOMAD::Param &p)
{
    std::pair<std::set<NOMAD::Param>::iterator,bool> ret;
    ret = m_params.insert(p);
    bool inserted = ret.second;
    if (!inserted)
    {
        // We will change the value of the parameter by erasing it,
        // and adding the new one.
        std::set<NOMAD::Param>::iterator it_oldparam = ret.first;
        m_params.erase(it_oldparam);
        ret = m_params.insert(p);
        inserted = ret.second;
    }
    return inserted;
}

bool NOMAD::Parameters::update(NOMAD::Param &p, const std::string value_string)
{
    // A parameter with this name, type, and category already exists.
    // Update its value.
    //
    if (!p.value_is_const())
    {
        std::cout << "VRM: update " << p.get_name() << " to (" << p.get_type_str() << ") " << value_string << std::endl;
        p.set_value(value_string);
        std::cout << "VRM: update " << p.get_name() << ", value is now " << p.get_value_str() << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Could not update this parameter value because it is const: " << p.get_name() << std::endl;
    }

    return false;
}

std::string NOMAD::Parameters::get_value_str(const std::string name) const
{
    std::string ret_str;
    const NOMAD::Param t_param(name, NOMAD::ParamValue(true));
    std::set<NOMAD::Param>::const_iterator it = m_params.find(t_param);
    const bool found = (it != m_params.end());
    if (found)
    {
        ret_str = (*it).get_value_str();
    }
    return ret_str;
}

bool NOMAD::Parameters::find(const std::string name, NOMAD::Param &foundparam) const
{
    const NOMAD::Param t_param(name, NOMAD::ParamValue(true));
    std::set<NOMAD::Param>::const_iterator it = m_params.find(t_param);
    const bool found = (it != m_params.end());
    if (found)
    {
        foundparam = (*it);
    }
    return found;
}

bool NOMAD::Parameters::is_defined(const std::string name) const
{
    std::set<NOMAD::Param>::const_iterator it;
    for (it = m_params.begin(); it != m_params.end(); it++)
    {
        if (name == it->get_name())
        {
            return true;
        }
    }
    return false;
}

bool NOMAD::Parameters::is_parameter_category(const std::string s)
{
    std::vector<std::string>::const_iterator it;
    it = std::find(m_param_categories.begin(), m_param_categories.end(), s);
    if (it != m_param_categories.end())
    {
        return true;
    }

    return false;
}

bool NOMAD::Parameters::is_runner_param(const std::string line)
{
    // Special case for a parameter that is named RUNNER...
    // Not very strong.
    size_t split_index = line.find(' ');
    size_t next_split_index = line.find(' ', split_index+1);
    if (next_split_index != std::string::npos)
        return false;
    std::string name = line.substr(0, split_index);
    if ("RUNNER" != name)
        return false;

    return true;
}

bool NOMAD::Parameters::parse_param_4fields(const std::string line,
            std::string &category, std::string &type_string,
            std::string &name, std::string &value_string)
{
    size_t split_index1 = line.find(' ');
    size_t split_index2 = line.find(' ', split_index1+1);
    size_t split_index3 = line.find(' ', split_index2+1);
    if (split_index1 == std::string::npos 
        || split_index2 == std::string::npos)
    {
        // category, type_string and name are mandatory.
        // split_index3 not found means that there is no default value defined
        // for this parameter.
        return false;
    }

    category        = line.substr(0, split_index1-0);
    type_string     = line.substr(split_index1+1, split_index2-split_index1-1);
    name            = line.substr(split_index2+1, split_index3-split_index2-1);
    if (split_index3 != std::string::npos)
    {
        value_string    = line.substr(split_index3+1, line.size()-split_index3);
    }

    return true;
}

bool NOMAD::Parameters::parse_param_2fields(const std::string line,
            std::string &name, std::string &value_string)
{
    size_t split_index = line.find(' ');
    if (split_index == std::string::npos)
        return false;

    // Contrary to parse_param_4fields(), here value_string is mandatory.
    name = line.substr(0, split_index-0);
    value_string = line.substr(split_index+1, line.size()-split_index);

    return true;
}

void NOMAD::Parameters::parse_line(std::string line)
{
    // Remove comments
    NOMAD::remove_comments(line);

    // 2 syntax accepted:
    // 1) Category Type Name Value
    // 2) Name Value
    // Fields are delimited by single spaces.
    //
    size_t split_index = line.find(' ');
    if (split_index != std::string::npos)
    {
        std::string first_field = line.substr(0, split_index);
        std::string category;
        std::string type_string;    // String representing the type, ex. "NOMAD::Double".
        std::string name;
        std::string value_string;   // String representing the value, ex. "2.345".
        if (is_parameter_category(first_field) && !is_runner_param(line))
        {
            // First field of the line identified as param category
            if (!parse_param_4fields(line, category, type_string, name, value_string))
            {
                std::cerr << "Could not parse this line: " << line << std::endl;
            }
            bool value_is_const = ("PROBLEM" == category);
            NOMAD::Param param(name, value_string, type_string, category, value_is_const);

            if (!this->add(param))
            {
                std::cerr << "Could not add parameter " << param.get_name() << std::endl;
                // VRM TODO add reasons
            }
        }
        else
        {
            // First field of the line not identified as param category.
            // Assume it is a parameter name.
            if (!parse_param_2fields(line, name, value_string))
            {
                std::cerr << "Could not parse this line: " << line << std::endl;
            }
            // This parameter should already exist. Update it.
            NOMAD::Param param(name, value_string);
            if (this->find(name, param))
            {
                this->update(param, value_string);
            }
            else
            {
                std::string def_category = "USER";
                std::string def_type = "std::string";
                std::cout << "Parameter " << name << " does not have a default value. ";
                std::cout << "Adding it with category = " << def_category << ", ";
                std::cout << "type = " << def_type << ", ";
                std::cout << "value = \"" << value_string << "\"" << std::endl;
                NOMAD::Param user_param(name, value_string, def_type, def_category, false);
                this->add(user_param);
            }
        }
        
    }
}

void NOMAD::Parameters::read_from_file(const std::string &filename)
{
    if (filename.empty())
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "File name is empty" );
    }

    std::string full_filename = NOMAD::fullpath(filename);
    std::ifstream fin;
    std::string err = "Could not open parameters file " + full_filename;

    // Check file existence
    if (!NOMAD::check_read_file (full_filename))
    {
        // The file does not exist, or is not readable
        throw NOMAD::Exception(__FILE__, __LINE__, err);
    }

    // Open the file
    fin.open( full_filename.c_str() );
    if (fin.fail())
    {
        // Could not open the file
        fin.close();
        throw NOMAD::Exception(__FILE__, __LINE__, err);
    }
    err.clear();


    std::string line;
    while (fin.good() && !fin.eof())
    {
        getline(fin, line);

        parse_line(line);
    }

    // Close file
    fin.close();

}

void NOMAD::Parameters::write_to_file(const std::string &filename) const
{
    // VRM: Not complete yet. TODO.
    std::cout << "VRM: Output to file " << filename << std::endl;
    std::cout << "VRM: Number of parameters: " << m_params.size() << std::endl;

    if (filename.empty())
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "File name is empty" );
    }
    std::string full_filename = NOMAD::fullpath(filename);
    std::cout << "VRM: full_filename " << full_filename << std::endl;
    std::string err = "Could not open parameters file " + full_filename + " for writing";

    // Warn user: if file exists, it will be overwritten.
    // TODO: cases where file exists but is not writable.
    if (NOMAD::check_write_file (full_filename))
    {
        std::cerr << "Warning: file " << full_filename << " will be overwritten." << std::endl;
    }

    // Open file for writing
    std::ofstream fout (full_filename.c_str(), std::ios::out );
    if (fout.fail())
    {
        fout.close();
        throw NOMAD::Exception(__FILE__, __LINE__, err);
    }

    for (std::set<NOMAD::Param>::const_iterator it = m_params.begin(); it != m_params.end(); it++)
    {
        fout << it->get_category() << " ";
        fout << it->get_type_str() << " ";
        fout << it->get_name() << " ";
        fout << it->get_value_str();
        fout << std::endl;
    }

    fout.close();
}

void NOMAD::Parameters::debug_display() const
{
    for (std::set<NOMAD::Param>::const_iterator it = m_params.begin(); it != m_params.end(); it++)
    {
        std::cout << it->get_category() << " ";
        std::cout << it->get_type_str() << " ";
        std::cout << it->get_name() << " ";
        std::cout << it->get_value_str();
        std::cout << std::endl;

    }
}
