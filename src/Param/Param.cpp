
#include "Param.hpp"
#include <Util/utils.hpp>
using namespace std;

// Constructors

Param::Param(std::string name,
             ParamValue paramvalue,
             std::string type_string,
             std::string category,
             bool value_is_const)
  : m_name(name),
    m_paramvalue(paramvalue),
    m_category(category),
    m_value_is_const(value_is_const)
{
    // VRM a revoir: paramvalue must be converted using type_string.
    init();
}

void Param::Param::init()
{
    // Convert name to capital letters
    NOMAD::toupper(m_name);

    // Validate
    if (!name_is_valid(m_name))
    {
        throw NOMAD::Exception("Param.cpp", __LINE__, "Param name is not valid");
    }
    if (!m_paramvalue.is_valid())
    {
        throw NOMAD::Exception("Param.cpp", __LINE__, "Param value is not valid");
    }
}

std::string Param::get_name() const
{
    return m_name;
}

void Param::set_name(const std::string name)
{
    if (!name_is_valid(name))
    {
        throw NOMAD::Exception("Param.cpp", __LINE__, "Param name is not valid");
    }
    m_name = name;
}

ParamValue Param::get_paramvalue() const
{
    return m_paramvalue;
}

void Param::set_paramvalue(const ParamValue paramvalue)
{
    if (m_value_is_const)
    {
        throw NOMAD::Exception("Param.cpp", __LINE__, "Param value is const and cannot be modified");
    }
    if (!paramvalue.is_valid())
    {
        throw NOMAD::Exception("Param.cpp", __LINE__, "Param value is not valid");
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
bool Param::name_is_valid(const std::string &name)
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

bool Param::operator< (const Param &p) const
{
    // Parameter name is the key, when adding to Parameters.
    // If a parameter already exists with this name, it will be 
    // ignored when adding to Parameters.
    return (m_name < p.m_name);
}

