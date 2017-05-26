
#ifndef __RUNNER400_PARAMVALUE__
#define __RUNNER400_PARAMVALUE__

#include <Math/Double.hpp>
#include <boost/variant.hpp>

typedef boost::variant<NOMAD::Double, bool> ValueVariant;


class ParamValue
{
private:
    ValueVariant _value;

public:
    // Constructors - One for each supported type, and more to avoid implicit conversions.
    ParamValue(const NOMAD::Double value);
    ParamValue(const bool value);
    ParamValue(const double value); // Non-explicit to allow assignments like ParamValue v = 1.23

    // Copy constructor
    ParamValue(const ParamValue &v);

    // Affectation operators.
    ParamValue & operator = ( const ParamValue & v );
    ParamValue & operator = ( const double & d );


    bool is_valid() const;

    // Get/Set
    ValueVariant get_value() const { return _value; }
    void set_value(const ValueVariant value);

    friend std::ostream& operator<<(std::ostream& stream, const ParamValue& v)
    {
        stream << v.get_value();
        return stream;
    }

};

#endif
