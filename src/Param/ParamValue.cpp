
#include "ParamValue.hpp"

// Constructors
ParamValue::ParamValue(const NOMAD::Double value)
  : _value(value)
{
}

ParamValue::ParamValue(const bool value)
  : _value(value)
{
}

ParamValue::ParamValue(const double value)
{
    // Need explicit conversion.
    _value = NOMAD::Double(value);
}

// Copy constructor
ParamValue::ParamValue(const ParamValue &v)
  : _value(v._value)
{
}

// Affectation operators
ParamValue & ParamValue::operator = ( const ParamValue & v )
{
    _value   = v._value;

    return *this;
}

ParamValue & ParamValue::operator = ( const double & d )
{
    _value   = d;

    return *this;
}


// Get/Set
void ParamValue::set_value(const ValueVariant value)
{
    _value = value;
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
};

// Validate the parameter value
bool ParamValue::is_valid() const
{
    Validator validator;
    bool is_valid = boost::apply_visitor( validator, _value);
    return is_valid;
}

