
#include "Param.hpp"
#include <Util/utils.hpp>

// Constructor with strings
NOMAD::Param::Param(std::string param_name,
             std::string value_string,
             std::string type_string,
             std::string category,
             bool value_is_const)
  : m_name(param_name),
    m_paramvalue(type_string, value_string),
    m_category(category),
    m_value_is_const(value_is_const)
{
    init();
}
    
// Constructor with ParamValue
NOMAD::Param::Param(std::string param_name,
             ParamValue paramvalue,
             std::string category,
             bool value_is_const)
  : m_name(param_name),
    m_paramvalue(paramvalue),
    m_category(category),
    m_value_is_const(value_is_const)
{
    init();
}

void NOMAD::Param::init()
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
        std::string err = "Param value \"" + m_paramvalue.get_value_str() + "\" is not valid for type " + m_paramvalue.get_type_str();
        throw NOMAD::Exception(__FILE__, __LINE__, err);
    }
}

std::string NOMAD::Param::get_name() const
{
    return m_name;
}

void NOMAD::Param::set_name(const std::string param_name)
{
    if (!name_is_valid(param_name))
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "Param name is not valid");
    }
    m_name = param_name;
}


// VRM set_value could use a template, but then calls like set_value(1.23) would
// become less simple to write.
void NOMAD::Param::set_value(const std::string value)
{
    if (m_value_is_const)
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "Param value is const and cannot be modified");
    }

    try
    {
        m_paramvalue.set_value(value);
    }
    catch (NOMAD::Exception &e)
    {
        std::cerr << "Could not set parameter " << this->get_name();
        std::cerr << " to value \"" << value << "\". Exception thrown: ";
        std::cerr << e.what();
        std::cerr << std::endl;
    }
}

void NOMAD::Param::set_value(const char* value)
{
    if (m_value_is_const)
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "Param value is const and cannot be modified");
    }

    try
    {
        m_paramvalue.set_value(value);
    }
    catch (NOMAD::Exception &e)
    {
        std::cerr << "Could not set parameter " << this->get_name();
        std::cerr << " to value \"" << value << "\". Exception thrown: ";
        std::cerr << e.what();
        std::cerr << std::endl;
    }
}

void NOMAD::Param::set_value(const NOMAD::Double value)
{
    if (m_value_is_const)
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "Param value is const and cannot be modified");
    }

    try
    {
        m_paramvalue.set_value(value);
    }
    catch (NOMAD::Exception &e)
    {
        std::cerr << "Could not set parameter " << this->get_name();
        std::cerr << " to value \"" << value << "\". Exception thrown: ";
        std::cerr << e.what();
        std::cerr << std::endl;
    }
}

void NOMAD::Param::set_value(const double value)
{
    if (m_value_is_const)
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "Param value is const and cannot be modified");
    }

    try
    {
        m_paramvalue.set_value(value);
    }
    catch (NOMAD::Exception &e)
    {
        std::cerr << "Could not set parameter " << this->get_name();
        std::cerr << " to value \"" << value << "\". Exception thrown: ";
        std::cerr << e.what();
        std::cerr << std::endl;
    }
}

void NOMAD::Param::set_value(const bool value)
{
    if (m_value_is_const)
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "Param value is const and cannot be modified");
    }

    try
    {
        m_paramvalue.set_value(value);
    }
    catch (NOMAD::Exception &e)
    {
        std::cerr << "Could not set parameter " << this->get_name();
        std::cerr << " to value \"" << value << "\". Exception thrown: ";
        std::cerr << e.what();
        std::cerr << std::endl;
    }
}

void NOMAD::Param::set_value(const int value)
{
    if (m_value_is_const)
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "Param value is const and cannot be modified");
    }

    try
    {
        m_paramvalue.set_value(value);
    }
    catch (NOMAD::Exception &e)
    {
        std::cerr << "Could not set parameter " << this->get_name();
        std::cerr << " to value \"" << value << "\". Exception thrown: ";
        std::cerr << e.what();
        std::cerr << std::endl;
    }
}

// Set value without verifying type. Input is a string.
void NOMAD::Param::set_value_str (const std::string value)
{
    if (m_value_is_const)
    {
        throw NOMAD::Exception(__FILE__, __LINE__, "Param value is const and cannot be modified");
    }
    try
    {
        m_paramvalue.set_value_str(value);
    }
    catch (NOMAD::Exception &e)
    {
        std::cerr << "Could not set parameter " << this->get_name();
        std::cerr << " to string value \"" << value << "\". Exception thrown: ";
        std::cerr << e.what();
        std::cerr << std::endl;
    }
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
bool NOMAD::Param::name_is_valid(const std::string &param_name)
{
    // Param name should be of the form:
    // Capital letter, followed by a combination of capital letters, numbers
    // and underscores, and ending by a capital letter or a number.

    // Note: std::regex is C++11 only, so it won't be used here.

    int last_i = param_name.length()-1;
    if (!is_capletter(param_name[0]))
    {
#ifdef DEBUG
        std::cerr << "Name is invalid: first character '" << param_name[0] << "' is not a capletter." << std::endl;
#endif
        return false;
    }
    for (int i = 1; i < last_i; i++) 
    {
        if (!is_capletter(param_name[i]) && !is_number(param_name[i]) && !is_underscore(param_name[i]))
        {
#ifdef DEBUG
            std::cerr << "Name is invalid: character '" << param_name[i] << "' is not a capletter, number, or underscore." << std::endl;
#endif
            return false;
        }
    }
    if (!is_capletter(param_name[last_i]) && !is_number(param_name[last_i]))
    {
#ifdef DEBUG
        std::cerr << "Name is invalid: last character = '" << param_name[last_i] << "' is not a capletter or number." << std::endl;
#endif
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

