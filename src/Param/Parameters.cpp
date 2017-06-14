
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
// If the parameter already exists, check category and type.
// If they mismatch with the input, an exception is thrown.
bool NOMAD::Parameters::add(const NOMAD::Param &param)
{
    std::pair<std::set<NOMAD::Param>::iterator,bool> ret;
    ret = m_params.insert(param);
    bool inserted = ret.second;
    if (!inserted)
    {
        // Parameter not inserted. A parameter with the same name
        // already exists.
        // We will erase it and add the new one.
        std::set<NOMAD::Param>::iterator it_oldparam = ret.first;
        // Verify category and type are the same, or else, throw an exception.
        if (it_oldparam->get_category() != param.get_category())
        {
            std::string err = "Category mismatch: New parameter " + param.get_name();
            err += " with category " + param.get_category();
            err += " already exists with different category " + it_oldparam->get_category();
            throw NOMAD::Exception(__FILE__, __LINE__, err );
        }
        if (it_oldparam->get_type_str() != param.get_type_str())
        {
            std::string err = "Category mismatch: New parameter " + param.get_name();
            err += " with type " + param.get_type_str();
            err += " already exists with different type " + it_oldparam->get_type_str();
            throw NOMAD::Exception(__FILE__, __LINE__, err );
        }
        m_params.erase(it_oldparam);
        ret = m_params.insert(param);
        inserted = ret.second;
    }
    return inserted;
}

// Return value:
// 1 - Parameter found and updated
// 0 - Parameter found but not updated
// -1 - Parameter not found.
int NOMAD::Parameters::update(const std::string param_name, const std::string value_string)
{
    // Work with caps
    std::string param_name_caps = param_name;
    NOMAD::toupper(param_name_caps);

    int ret_value = -1;

    // VRM current implementation is not optimal.
    // There is redundancy in search, plus search itself could use std functions.
    if (is_defined(param_name_caps))
    {
        std::set<NOMAD::Param>::iterator it;

        for (it = m_params.begin(); it != m_params.end(); it++)
        {
            if (it->get_name() == param_name_caps)
            {
                if (it->value_is_const())
                {
                    ret_value = 0;
                    std::cerr << "Could not update this parameter value because it is const: " << param_name << std::endl;
                }
                else
                {
                    try
                    {
                        // Create a new Param based on the found param, but
                        // using the new value.
                        Param newparam = (*it);
                        newparam.set_value_str(value_string);
                        // Remove the current param and add the new one.
                        m_params.erase(it);
                        std::pair<std::set<NOMAD::Param>::iterator,bool> ret;
                        ret = m_params.insert(newparam);
                        ret_value = ret.second;
                    }
                    catch (NOMAD::Exception &e)
                    {
                        // Problem when updating value, do not update.
                        ret_value = 0;
                    }
                }
            }
        }
    }

    return ret_value;
}

bool NOMAD::Parameters::remove(const std::string param_name)
{
    // Work with caps
    std::string param_name_caps = param_name;
    NOMAD::toupper(param_name_caps);

    bool param_removed = false;
    if (!is_defined(param_name_caps))
    {
        std::string err = "There is no parameter " + param_name + " to remove.";
        std::cerr << err << std::endl;
    }
    std::set<NOMAD::Param>::iterator it;
    for (it = m_params.begin(); it != m_params.end(); it++)
    {
        if (it->get_name() == param_name_caps)
        {
            m_params.erase(it);
            param_removed = true;
        }
    }

    if (it == m_params.end())
    {
        // Sanity check. We should never get there.
        std::string err = "Could not remove parameter " + param_name;
        NOMAD::Exception(__FILE__, __LINE__, err);
    }

    return param_removed;
}

bool NOMAD::Parameters::is_defined(const std::string param_name) const
{
    // Work with caps
    std::string param_name_caps = param_name;
    NOMAD::toupper(param_name_caps);

    std::set<NOMAD::Param>::const_iterator it;

    for (it = m_params.begin(); it != m_params.end(); it++)
    {
        if (it->get_name() == param_name_caps)
        {
            break;
        }
    }
    const bool found = (it != m_params.end());

    return found;
}


std::string NOMAD::Parameters::get_value_str(const std::string param_name) const
{
    // Work with caps
    std::string param_name_caps = param_name;
    NOMAD::toupper(param_name_caps);

    std::set<NOMAD::Param>::const_iterator it;
    std::string ret_str;

    for (it = m_params.begin(); it != m_params.end(); it++)
    {
        if (it->get_name() == param_name_caps)
        {
            ret_str = it->get_value_str();
        }
    }

    return ret_str;
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
    std::string param_name = line.substr(0, split_index);
    if ("RUNNER" != param_name)
        return false;

    return true;
}

bool NOMAD::Parameters::parse_param_4fields(const std::string line,
            std::string &category, std::string &type_string,
            std::string &param_name, std::string &value_string)
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
    param_name      = line.substr(split_index2+1, split_index3-split_index2-1);
    if (split_index3 != std::string::npos)
    {
        value_string    = line.substr(split_index3+1, line.size()-split_index3);
    }

    return true;
}

bool NOMAD::Parameters::parse_param_2fields(const std::string line,
            std::string &param_name, std::string &value_string)
{
    size_t split_index = line.find(' ');
    if (split_index == std::string::npos)
        return false;

    // Contrary to parse_param_4fields(), here value_string is mandatory.
    param_name = line.substr(0, split_index-0);
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
        std::string param_name;
        std::string value_string;   // String representing the value, ex. "2.345".
        if (is_parameter_category(first_field) && !is_runner_param(line))
        {
            // First field of the line identified as param category
            if (!parse_param_4fields(line, category, type_string, param_name, value_string))
            {
                std::cerr << "Could not parse this line: " << line << std::endl;
            }
            // VRM to be modified.
            // When reading default configuration file, and then reading a problem file,
            // the value should be updatable.
            bool value_is_const = ("PROBLEM" == category);
            NOMAD::Param param(param_name, value_string, type_string, category, value_is_const);

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
            if (!parse_param_2fields(line, param_name, value_string))
            {
                std::cerr << "Could not parse this line: " << line << std::endl;
            }
            NOMAD::toupper(param_name);

            // Update this parameter if it already exists.
            // Otherwise, create an USER parameter.
            if (this->update(param_name, value_string) < 0)
            {
                std::string def_category = "USER";
                std::string def_type = "std::string";
                std::cout << "Parameter " << param_name << " does not have a default value. ";
                std::cout << "Adding it with category = " << def_category << ", ";
                std::cout << "type = " << def_type << ", ";
                std::cout << "value = \"" << value_string << "\"" << std::endl;
                NOMAD::Param user_param(param_name, value_string, def_type, def_category, false);
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
