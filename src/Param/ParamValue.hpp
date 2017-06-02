
#ifndef __RUNNER400_PARAMVALUE__
#define __RUNNER400_PARAMVALUE__

#include <Math/Double.hpp>
#include <boost/variant.hpp>

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

    // Copy constructor
    ParamValue(const ParamValue &v);

    // Affectation operators.
    ParamValue & operator = ( const ParamValue & v );
    ParamValue & operator = ( const double & d );
    ParamValue & operator = ( const char* & s );


    // Comparison operators
    inline bool operator==(const ParamValue& rhs) const {
        return m_valuevariant == rhs.m_valuevariant;
    }
    inline bool operator!=(const ParamValue& rhs) const {
        return !(*this == rhs);
    }
    //bool operator< (const ParamValue &paramvalue) const;
    

    bool is_valid() const;

    // Get/Set
    template <typename T>
    T get_value() const
    {
        return boost::get<T>(m_valuevariant);
    }
    ValueVariant get_valuevariant() const { return m_valuevariant; }
    void set_value(const ValueVariant value) { m_valuevariant = value; }

    friend std::ostream& operator<<(std::ostream& stream, const ParamValue& v)
    {
        stream << v.get_valuevariant();
        return stream;
    }

};

#endif
