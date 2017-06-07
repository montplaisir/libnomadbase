
#include "ParamValue.hpp"

// Constructors
NOMAD::ParamValue::ParamValue(const NOMAD::Double value)
  : m_valuevariant(value)
{
}

NOMAD::ParamValue::ParamValue(const bool value)
  : m_valuevariant(value)
{
}

NOMAD::ParamValue::ParamValue(const std::string value)
  : m_valuevariant(value)
{
}

NOMAD::ParamValue::ParamValue(const double value)
{
    // Need explicit conversion.
    m_valuevariant = NOMAD::Double(value);
}

NOMAD::ParamValue::ParamValue(const char* value)
{
    // Need explicit conversion.
    m_valuevariant = std::string(value);
}

NOMAD::ParamValue::ParamValue(const std::string type_string, const std::string value_string)
{
    //std::cout << "VRM: create ParamValue with type = " << type_string << ", value = " << value_string << std::endl;
    update_valuevariant(type_string, value_string);
}

void NOMAD::ParamValue::update_valuevariant(const std::string type_string, const std::string value_string)
{
    std::string err = "Error: " + type_string + " value ill-defined: \"" + value_string + "\"";

    if ("std::string" == type_string)
    {
        //std::cout << "VRM: update string to " << value_string << std::endl;
        m_valuevariant = value_string;
    }
    else if ("NOMAD::Double" == type_string)
    {
        NOMAD::Double value;
        if (!value_string.empty() && !value.atof(value_string))
        {
            throw NOMAD::Exception(__FILE__,__LINE__,err);
        }
        m_valuevariant = value;
    }
    else if ("bool" == type_string)
    {
        bool value;
        std::string bool_string = value_string;
        NOMAD::toupper(bool_string);
        if ("TRUE" == bool_string || "1" == bool_string || "YES" == bool_string)
        {
            value = true;
        }
        else if ("FALSE" == bool_string || "0" == bool_string || "NO" == bool_string)
        {
            value = false;
        }
        else
        {
            throw NOMAD::Exception(__FILE__,__LINE__,err);
        }
        m_valuevariant = value;
    }

}

// Copy constructor
NOMAD::ParamValue::ParamValue(const NOMAD::ParamValue &v)
  : m_valuevariant(v.m_valuevariant)
{
}

// Affectation operators
NOMAD::ParamValue & NOMAD::ParamValue::operator = ( const NOMAD::ParamValue & v )
{
    m_valuevariant = v.m_valuevariant;

    return *this;
}

NOMAD::ParamValue & NOMAD::ParamValue::operator = ( const double & d )
{
    m_valuevariant = d;

    return *this;
}

NOMAD::ParamValue & NOMAD::ParamValue::operator = ( const char* & s )
{
    m_valuevariant = std::string(s);

    return *this;
}

// Class used to validate the variant ParamValue - see is_valid() below.
class Validator : public boost::static_visitor<bool>
{
public:
    bool operator()(const bool &b) const
    {
        return true;
    }
    bool operator()(const NOMAD::Double &d) const
    {
        // Accept undefined NOMAD::Double
        /* if (!d.is_defined())
        {
            return false;
        }*/
        return true;
    }
    bool operator()(const std::string &s) const
    {
        // Accept empty strings.
        return true;
    }
};

// Validate the parameter value
bool NOMAD::ParamValue::is_valid() const
{
    Validator validator;
    bool is_valid = boost::apply_visitor( validator, m_valuevariant);
    return is_valid;
}

// Class used to convert the variant to string.
class ConverterToString : public boost::static_visitor<std::string>
{
public:
    std::string operator()(const bool &v) const
    {
        return std::string("bool");
    }
    std::string operator()(const NOMAD::Double &v) const
    {
        return std::string("NOMAD::Double");
    }
    std::string operator()(const std::string &v) const
    {
        return std::string("std::string");
    }
};

// Convert the parameter type to a string describing the type.
std::string NOMAD::ParamValue::type_string() const
{
    ConverterToString converter;
    std::string ret_str = boost::apply_visitor( converter, m_valuevariant);
    return ret_str;
}




