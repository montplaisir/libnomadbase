
#ifndef __RUNNER400_PARAMVALUE__
#define __RUNNER400_PARAMVALUE__

#include <Math/Double.hpp>
#include <boost/variant.hpp>

#include "nomad_nsbegin.hpp"

typedef boost::variant<NOMAD::Double, bool, std::string> ValueVariant;

class ParamValue
{
private:
    ValueVariant m_valuevariant;

public:
    // Constructors - One for each supported type, and more to avoid implicit conversions.
    // Non-explicit to allow assignments like ParamValue v = 1.23
    ParamValue(const NOMAD::Double value);
    ParamValue(const bool value);
    ParamValue(const std::string value);
    ParamValue(const double value);
    ParamValue(const char* value);

    // Constructor from string values.
    ParamValue(const std::string type_string, const std::string value_string);

    // Copy constructor
    ParamValue(const NOMAD::ParamValue &v);

    // Affectation operators.
    ParamValue & operator = ( const NOMAD::ParamValue & v );
    ParamValue & operator = ( const double & d );
    ParamValue & operator = ( const char* & s );


    // Comparison operators
    inline bool operator==(const NOMAD::ParamValue& rhs) const {
        return m_valuevariant == rhs.m_valuevariant;
    }
    inline bool operator!=(const NOMAD::ParamValue& rhs) const {
        return !(*this == rhs);
    }

    bool is_valid() const;

    // Get/Set
    template <typename T>
    T get_value() const
    {
        return boost::get<T>(m_valuevariant);
    }
    ValueVariant get_valuevariant() const { return m_valuevariant; }
    void set_valuevariant(const ValueVariant value) { m_valuevariant = value; }
    // Update valuevariant, assuming the input string is for a value of the same type
    // as the current valuevariant.
    void update_valuevariant(const std::string type_string, const std::string value_string);

    friend std::ostream& operator<<(std::ostream& stream, const NOMAD::ParamValue& v)
    {
        stream << v.get_valuevariant();
        return stream;
    }

    // Return a string for the type in ValueVariant.
    // Ex. "NOMAD::Double", "bool", "std::string", etc.
    std::string type_string() const;

};

#include "nomad_nsend.hpp"

#endif
