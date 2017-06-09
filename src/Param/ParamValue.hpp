
#ifndef __RUNNER400_PARAMVALUE__
#define __RUNNER400_PARAMVALUE__

#include <Math/Double.hpp>

#include "nomad_nsbegin.hpp"

class ParamValue
{
private:
    std::string m_type_str;
    std::string m_value_str;

public:
    // Constructors - One for each supported type, and more to avoid implicit conversions.
    // Non-explicit to allow assignments like ParamValue v = 1.23
    ParamValue(const NOMAD::Double value);
    ParamValue(const double value);
    ParamValue(const std::string value);
    ParamValue(const char* value);
    ParamValue(const int value);
    ParamValue(const bool value);

    // General constructor.
    ParamValue(const std::string type_string, const std::string value_string);

    // Copy constructor
    ParamValue(const NOMAD::ParamValue &v);

    // Affectation operators.
    ParamValue & operator = ( const NOMAD::ParamValue & v );


    // Comparison operators
    inline bool operator==(const NOMAD::ParamValue& rhs) const {
        return m_type_str == rhs.m_type_str && m_value_str == rhs.m_value_str;
    }
    inline bool operator!=(const NOMAD::ParamValue& rhs) const {
        return !(*this == rhs);
    }

    bool is_valid() const;

    // Get/Set
    std::string get_type_str() const { return m_type_str; }

    NOMAD::Double   get_value_double()              const;
    bool            get_value_bool()                const;
    int             get_value_int()                 const;
    std::string     get_value_str()                 const { return m_value_str; }
    std::string     get_value_str(const int index)  const;

    void set_value(const NOMAD::Double value);
    void set_value(const double value);
    void set_value(const bool value);
    void set_value(const int value);
    void set_value(const std::string value) { m_value_str = value; }
    void set_value(const char* value);

    // operator<<
    friend std::ostream& operator<<(std::ostream& stream, const NOMAD::ParamValue& v)
    {
        stream << v.get_value_str();
        return stream;
    }

};

#include "nomad_nsend.hpp"

#endif
