
#ifndef __RUNNER400_PARAM__
#define __RUNNER400_PARAM__

#include <string>

#include <Util/Exception.hpp>

#include "ParamValue.hpp"

// Class for all Parameters.


class Param
{
private:
    std::string     m_category;  // Ex. ALGO, PROBLEM, ... // VRM make an ENUM
    std::string     m_name;      // Will be converted to caps
    ParamValue      m_paramvalue;
    bool            m_value_is_const;

    void    init();

public:
    // Constructor
    Param(std::string name,     // Name of the parameter. Naming has some rules.
          ParamValue paramvalue,     // Value type defined through ParamValue
          std::string category = std::string(), // ALGORITHM, PROBLEM parameter, etc.
          bool value_is_const = true);      // Can we modify this parameter's value?

    // Destructor
    virtual ~Param() {}

    // Get/Set parameter name and value
    // Setting name has some validation.
    std::string get_name() const;
    void set_name(const std::string name);

    ParamValue get_paramvalue() const;
    template<typename T>
    T get_value() const
    {
        return boost::get<T>(m_paramvalue.get_valuevariant());
    }

    void set_paramvalue(const ParamValue paramvalue);

    bool value_is_const() const { return m_value_is_const; }

    // Validate the string as a parameter name
    static bool name_is_valid(const std::string &name);
    // Validate the paramvalue
    static bool value_is_valid(const ParamValue &paramvalue);

    // Comparison operator for insertion in set
    bool operator< (const Param &p) const;
};

#endif
