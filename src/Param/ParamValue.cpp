
#include "ParamValue.hpp"

// Constructors

// Constructor for NOMAD::Double.
NOMAD::ParamValue::ParamValue(const NOMAD::Double value)
  : m_type_str("NOMAD::Double"),
    m_type_unsupported(false),
    m_value_str(value.tostring())
{
}

// Constructor for double.
// Convert to NOMAD::Double.
NOMAD::ParamValue::ParamValue(const double value)
  : m_type_str("NOMAD::Double"),
    m_type_unsupported(false),
    m_value_str()
{
    std::stringstream ss;
    ss << value;
    m_value_str = ss.str();
}

// Constructor for std::string.
NOMAD::ParamValue::ParamValue(const std::string value)
  : m_type_str("std::string"),
    m_type_unsupported(false),
    m_value_str(value)
{
}

// Constructor for char*.
// Convert to std::string.
NOMAD::ParamValue::ParamValue(const char* value)
  : m_type_str("std::string"),
    m_type_unsupported(false),
    m_value_str(value)
{
}

// Constructor for int.
NOMAD::ParamValue::ParamValue(const int value)
  : m_type_str("int"),
    m_type_unsupported(false),
    m_value_str()
{
    std::stringstream ss;
    ss << value;
    m_value_str = ss.str();
}

// Constructor for bool.
NOMAD::ParamValue::ParamValue(const bool value)
  : m_type_str("bool"),
    m_type_unsupported(false),
    m_value_str()
{
    std::stringstream ss;
    ss << value;
    m_value_str = ss.str();
}

// Constructor for a type given as argument (as string).
// Special cases:
//  - If the type is NOMAD::Double and the value is an empty string,
// change it to NOMAD::DEFAULT_UNDEF_STR ("NaN").
//  - If we know this type is not supported, set flag to true.
NOMAD::ParamValue::ParamValue(const std::string type_string, const std::string value_string)
  : m_type_str(type_string),
    m_type_unsupported(false),
    m_value_str(value_string)
{
    if ("NOMAD::Double" == type_string && value_string.empty())
    {
        m_value_str = NOMAD::DEFAULT_UNDEF_STR;
    }
    if (!is_type_supported(type_string))
    {
        m_type_unsupported = true;
    }
}


// Copy constructor
NOMAD::ParamValue::ParamValue(const NOMAD::ParamValue &v)
  : m_type_str(v.m_type_str),
    m_type_unsupported(v.m_type_unsupported),
    m_value_str(v.m_value_str)
{
}

// Affectation operators
NOMAD::ParamValue & NOMAD::ParamValue::operator = ( const NOMAD::ParamValue & v )
{
    m_type_str          = v.m_type_str;
    m_type_unsupported  = v.m_type_unsupported;
    m_value_str         = v.m_value_str;

    return *this;
}

// Validate the type given by m_type_string.
// Unsupported type means the user has to do the conversion from string. There
// is no constructor for this type and no output to this type.
bool NOMAD::ParamValue::is_type_supported(std::string type_string)
{
    bool is_sup = false;
    if ( ("NOMAD::Double" == type_string) || ("std::string" == type_string)
         || ("bool" == type_string) || ("int" == type_string) )
    {
        is_sup = true;
    }

    return is_sup;
}

// Validate the parameter value
bool NOMAD::ParamValue::is_valid() const
{
    bool is_valid = false;
    
    // Validate that value string can be converted to type given by m_type_string.
    if ("NOMAD::Double" == m_type_str)
    {
        // Accept a NOMAD::Double even if it is not defined.
        try
        {
            NOMAD::Double d = get_value_double();
            is_valid = true;
        }
        catch (NOMAD::Exception &e)
        {
            is_valid = false;
        }
    }
    else if ("std::string" == m_type_str)
    {
        // all strings are valid for now.
        is_valid = true;
    }
    else if ("bool" == m_type_str)
    {
        try
        {
            get_value_bool();
            is_valid = true;
        }
        catch (NOMAD::Exception &e)
        {
            is_valid = false;
        }
    }
    else if ("int" == m_type_str)
    {
        try
        {
            get_value_int();
            is_valid = true;
        }
        catch (NOMAD::Exception &e)
        {
            is_valid = false;
        }
    }
    else
    {
        // If we know this type is unsupported, then the value is valid.
        is_valid = m_type_unsupported;
    }

    return is_valid;
}

NOMAD::Double NOMAD::ParamValue::get_value_double() const
{
    NOMAD::Double d = 0.0;
    std::string err = "ERROR: Could not convert this value to NOMAD::Double : " + m_value_str;
    if ("NOMAD::Double" != m_type_str)
    {
        throw NOMAD::Exception(__FILE__,__LINE__,err);
    }

    if (!d.atof(m_value_str))
    {
        throw NOMAD::Exception(__FILE__,__LINE__,err);
    }

    return d;
}

bool NOMAD::ParamValue::get_value_bool() const
{
    bool b = false;
    std::string err = "ERROR: Could not convert this value to bool : " + m_value_str;

    if ("bool" != m_type_str)
    {
        throw NOMAD::Exception(__FILE__,__LINE__,err);
    }

    int intb = NOMAD::string_to_bool(m_value_str);
    if (intb < 0)
    {
        throw NOMAD::Exception(__FILE__,__LINE__,err);
    }
    b = intb;

    return b;
}

int NOMAD::ParamValue::get_value_int() const
{
    int i = 0;
    std::string err = "ERROR: Could not convert this value to int : " + m_value_str;

    if ("int" != m_type_str)
    {
        throw NOMAD::Exception(__FILE__,__LINE__,err);
    }
    
    if (!NOMAD::atoi(m_value_str, i))
    {
        throw NOMAD::Exception(__FILE__,__LINE__,err);
    }

    return i;
}


// Get string value at index
std::string NOMAD::ParamValue::get_value_str(const int index) const
{
    std::string ret_str = "";
    size_t split_index1 = 0;
    size_t split_index2 = m_value_str.find(' ', split_index1+1);

    if (0 == index)
    {
        // start and end of substr is different for this case.
        ret_str = m_value_str.substr(split_index1, split_index2);
    }
    else
    {
        int i = 0;
        for (; i < index && split_index1 != std::string::npos
                         && split_index2 != std::string::npos; i++)
        {
            split_index1 = split_index2;
            split_index2 = m_value_str.find(' ', split_index1+1);
        }
        if (i < index)
        {
            // Reached end of string before reaching substring for index
            std::cout << "Warning: End of string reached before index " << index << std::endl;
        }
        ret_str = m_value_str.substr(split_index1+1, split_index2-split_index1-1);
    }

    return ret_str;
}


void NOMAD::ParamValue::set_value(const NOMAD::Double value)
{
    m_type_str = "NOMAD::Double";
    m_value_str = value.tostring();
}

void NOMAD::ParamValue::set_value(const double value)
{
    m_type_str = "NOMAD::Double";
    std::stringstream ss;
    ss << value;
    m_value_str = ss.str();
}

void NOMAD::ParamValue::set_value(const bool value)
{
    m_type_str = "bool";
    std::stringstream ss;
    ss << value;
    m_value_str = ss.str();
}

void NOMAD::ParamValue::set_value(std::string value)
{
    m_type_str = "std::string";
    m_value_str = value;
}

void NOMAD::ParamValue::set_value(const char* value)
{
    m_type_str = "std::string";
    m_value_str = value;
}

void NOMAD::ParamValue::set_value(const int value)
{
    m_type_str = "int";
    std::stringstream ss;
    ss << value;
    m_value_str = ss.str();
}


// VRM this code will be useful for converting string to type. keep it for reference
/*
void NOMAD::ParamValue::update_value_str(const std::string type_string, const std::string value_string)
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
*/
