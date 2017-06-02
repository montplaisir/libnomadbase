
#include "ParamValue.hpp"

// Constructors
ParamValue::ParamValue(const NOMAD::Double value)
  : m_valuevariant(value)
{
}

ParamValue::ParamValue(const bool value)
  : m_valuevariant(value)
{
}

ParamValue::ParamValue(const std::string value)
  : m_valuevariant(value)
{
}

ParamValue::ParamValue(const double value)
{
    // Need explicit conversion.
    m_valuevariant = NOMAD::Double(value);
}

ParamValue::ParamValue(const char* value)
{
    // Need explicit conversion.
    m_valuevariant = std::string(value);
}

// Copy constructor
ParamValue::ParamValue(const ParamValue &v)
  : m_valuevariant(v.m_valuevariant)
{
}

// Affectation operators
ParamValue & ParamValue::operator = ( const ParamValue & v )
{
    m_valuevariant = v.m_valuevariant;

    return *this;
}

ParamValue & ParamValue::operator = ( const double & d )
{
    m_valuevariant = d;

    return *this;
}

ParamValue & ParamValue::operator = ( const char* & s )
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
        if (!d.is_defined())
        {
            return false;
        }
        return true;
    }
    bool operator()(const std::string &s) const
    {
        if (s.empty())
        {
            return false;
        }
        return true;
    }
};

// Validate the parameter value
bool ParamValue::is_valid() const
{
    Validator validator;
    bool is_valid = boost::apply_visitor( validator, m_valuevariant);
    return is_valid;
}

