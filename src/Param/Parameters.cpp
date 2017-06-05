
#include <algorithm>
#include <fstream>
#include <Util/fileutils.hpp>
#include <Util/utils.hpp>
#include "Parameters.hpp"

// Initialize parameter categories static member.
std::string categories[] = {"ALGO", "PROBLEM", "RUNNER", "USER"};
const std::vector<std::string> Parameters::m_param_categories(categories, categories + sizeof(categories) / sizeof (std::string));

Parameters::Parameters()
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

bool Parameters::is_parameter_category(const std::string s)
{
    std::vector<std::string>::const_iterator it;
    it = std::find(m_param_categories.begin(), m_param_categories.end(), s);
    if (it != m_param_categories.end())
    {
        return true;
    }

    return false;
}

bool Parameters::is_runner_param(const std::string line)
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

bool Parameters::parse_param_4fields(const std::string line,
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

//std::cout << "VRM: line:" << std::endl;
//std::cout << line << std::endl;
//std::cout << "VRM: indices: " << split_index1 << " " << split_index2 << " " << split_index3 << std::endl;
    category        = line.substr(0, split_index1-0);
    type_string     = line.substr(split_index1+1, split_index2-split_index1-1);
    name            = line.substr(split_index2+1, split_index3-split_index2-1);
    if (split_index3 != std::string::npos)
    {
        value_string    = line.substr(split_index3+1, line.size()-split_index3);
    }

    return true;
}

bool Parameters::parse_param_2fields(const std::string line,
            std::string &name, std::string &value_string)
{
    size_t split_index = line.find(' ');
    if (split_index == std::string::npos)
        return false;

    // Contrary to parse_param_4fields(), here value_string is mandatory.
    name = line.substr(0, split_index);
    value_string = line.substr(split_index, line.size());

    return true;
}

void Parameters::parse_line(std::string line)
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
            //std::cout << "VRM Syntax 1 for line: " << line << std::endl;
            // First field of the line identified as param category
            if (!parse_param_4fields(line, category, type_string, name, value_string))
            {
                std::cerr << "Could not parse this line: " << line << std::endl;
            }
            bool value_is_const = ("PROBLEM" == category);
            /*
            std::cout << "VRM name: \"" << name << "\"" << std::endl;
            std::cout << "VRM value_string: \"" << value_string << "\"" << std::endl;
            std::cout << "VRM type_string: \"" << type_string << "\"" << std::endl;
            std::cout << "VRM category: \"" << category << "\"" << std::endl;
            std::cout << "VRM value_is_const: \"" << value_is_const << "\"" << std::endl;
            */
            Param param(name, value_string, type_string, category, value_is_const);

            // VRM value will all be strings for now, to review.
            // TODO convert to NOMAD::Double, etc.
            if (!this->add(param))
            {
                std::cerr << "Could not add parameter " << param.get_name() << std::endl;
                // VRM TODO add reasons
            }
        }
        else
        {
            //std::cout << "VRM Syntax 2 for line: " << line << std::endl;
            // First field of the line not identified as param category.
            // Assume it is a parameter name.
            if (!parse_param_2fields(line, name, value_string))
            {
                std::cerr << "Could not parse this line: " << line << std::endl;
            }
            // This parameter should already exist. Update it.
            Param param(name, value_string);
            if (this->find(name, param))
            {
                this->add(param);   // VRM a revoir: add a param that already exists!! an update() function should be made instead.
            }
            else
            {
                std::cout << "Parameter " << name << " not initialized with a default value. ";
                std::cout << "Adding it as a USER category parameter. " << std::endl;
                Param user_param(name, value_string, "std::string", "USER", false);
                this->add(user_param);
            }
        }
        
    }
}

void Parameters::read_from_file(const std::string &filename)
{
    std::cout << "VRM: read_from_file " << filename << std::endl;
    if (filename.empty())
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "File name is empty" );
    }

    std::string full_filename = NOMAD::fullpath(filename);
    std::cout << "VRM: full_filename " << full_filename << std::endl;
    std::ifstream fin;
    std::string err = "Could not open parameters file " + full_filename;

    // Check file existence
    if (!NOMAD::check_read_file (full_filename))
    {
        // The file does not exist
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
