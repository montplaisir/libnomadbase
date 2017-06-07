
#include "Param.hpp"
#include <Util/utils.hpp>
using namespace std;

// Constructors

// Constructor from string values
NOMAD::Param::Param(std::string name,
             std::string value_string,
             std::string type_string,
             std::string category,
             bool value_is_const)
  : m_name(name),
    m_paramvalue(type_string, value_string),
    m_category(category),
    m_value_is_const(value_is_const)
{
    init();
}
    

// General constructor
NOMAD::Param::Param(std::string name,
             NOMAD::ParamValue paramvalue,
             std::string category,
             bool value_is_const)
  : m_name(name),
    m_paramvalue(paramvalue),
    m_category(category),
    m_value_is_const(value_is_const)
{
    init();
}

void NOMAD::Param::Param::init()
{
    // Convert name to capital letters
    NOMAD::toupper(m_name);

    // Validate
    if (!name_is_valid(m_name))
    {
        std::string err = "Param name \"" + m_name + "\" is not valid";
        throw NOMAD::Exception(__FILE__, __LINE__, err);
    }
    if (!m_paramvalue.is_valid())
    {
        //std::string err = "Param value is not valid";
        throw NOMAD::Exception(__FILE__, __LINE__, "Param value is not valid");
    }
}

std::string NOMAD::Param::get_name() const
{
    return m_name;
}

void NOMAD::Param::set_name(const std::string name)
{
    if (!name_is_valid(name))
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "Param name is not valid");
    }
    m_name = name;
}

NOMAD::ParamValue NOMAD::Param::get_paramvalue() const
{
    return m_paramvalue;
}

std::string NOMAD::Param::get_value_str() const
{
    std::string ret_str = "";

    if (this->get_type() == "std::string")
    {
        ret_str = this->get_value<std::string>();
    }
    else if (this->get_type() == "bool")
    {
        bool value = this->get_value<bool>();
        ret_str = (value) ? "true" : "false";
    }
    else if (this->get_type() == "NOMAD::Double")
    {
        NOMAD::Double d = this->get_value<NOMAD::Double>();
        ret_str = d.tostring();
    }
    else
    {
        std::string err = "Unknown parameter type: " + this->get_type();
        throw NOMAD::Exception(__FILE__,__LINE__,err);
    }

    return ret_str;
}

void NOMAD::Param::set_value_str(const std::string value_string)
{
    try
    {
        m_paramvalue.update_valuevariant(this->get_type(), value_string);
        std::cout << "VRM: set_value_str, m_paramvalue is now: " << get_value_str() << std::endl;
    }
    catch (NOMAD::Exception &e)
    {
        std::cerr << "Could not set parameter " << this->get_name();
        std::cerr << " to value \"" << value_string << "\". Exception thrown: ";
        std::cerr << e.what();
        std::cerr << std::endl;
    }
}


void NOMAD::Param::set_paramvalue(const NOMAD::ParamValue paramvalue)
{
    if (m_value_is_const)
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "Param value is const and cannot be modified");
    }
    if (!paramvalue.is_valid())
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "Param value is not valid");
    }
    m_paramvalue = paramvalue;
}

bool is_capletter(const char &c)
{
    if (c < 'A' || c > 'Z')
    {
        return false;
    }
    return true;
}

bool is_number(const char &c)
{
    if (c < '0' || c > '9')
    {
        return false;
    }
    return true;
}

bool is_underscore(const char &c)
{
    if (c == '_')
    {
        return true;
    }
    return false;
}

// Validate the string as a parameter name
bool NOMAD::Param::name_is_valid(const std::string &name)
{
    // Param name should be of the form:
    // Capital letter, followed by a combination of capital letters, numbers
    // and underscores, and ending by a capital letter or a number.

    // Note: std::regex is C++11 only, so it won't be used here.

    int last_i = name.length()-1;
    if (!is_capletter(name[0]))
    {
        cerr << "Name is invalid: first character '" << name[0] << "' is not a capletter." << endl;
        return false;
    }
    for (int i = 1; i < last_i; i++) 
    {
        if (!is_capletter(name[i]) && !is_number(name[i]) && !is_underscore(name[i]))
        {
            cerr << "Name is invalid: character '" << name[i] << "' is not a capletter, number, or underscore." << endl;
            return false;
        }
    }
    if (!is_capletter(name[last_i]) && !is_number(name[last_i]))
    {
        cerr << "Name is invalid: last character = '" << name[last_i] << "' is not a capletter or number." << endl;
        return false;
    }
    return true;
}

bool NOMAD::Param::operator< (const NOMAD::Param &p) const
{
    // Parameter name is the key, when adding to Parameters.
    // If a parameter already exists with this name, it will be 
    // ignored when adding to Parameters.
    return (m_name < p.m_name);
}

