
#ifndef __RUNNER400_PARAM__
#define __RUNNER400_PARAM__

#include <string>

#include <Util/Exception.hpp>

#include "ParamValue.hpp"

#include "nomad_nsbegin.hpp"

// Class for all Parameters.

class Param
{
private:
    std::string         m_name;         // Name of the parameter. Will be converted to caps.
                                        // Naming has some rules.
    NOMAD::ParamValue   m_paramvalue;   // See ValueVariant. Type could be std::string,
                                        // NOMAD::Double, bool, etc.
    std::string         m_category;     // ALGO, PROBLEM, RUNNER, USER
    bool                m_value_is_const;   // If we can modify this parameter's value

    void    init();

public:
    // Constructor from strings
    Param(std::string name,
          std::string value_string,         // String representing ParamValue.
          std::string type_string,          // String representing type for ParamValue.
                                            // See ValueVariant.
                                            // Could be "std::string", "NOMAD::Double", etc.
          std::string category = "USER",
          bool value_is_const = true);
    // Constructor
    Param(std::string name,
          NOMAD::ParamValue paramvalue,     // Value type defined through ParamValue
          std::string category = "USER",
          bool value_is_const = true);

    // Destructor
    virtual ~Param() {}

    // Get/Set
    // Setting name has some validation.
    std::string get_name() const;
    void set_name(const std::string name);

    // Return value as a ParamValue
    NOMAD::ParamValue get_paramvalue() const;
    // Return value in its type
    template<typename T>
    T get_value() const
    {
        return boost::get<T>(m_paramvalue.get_valuevariant());
    }
    // Return value converted to string
    std::string get_value_str() const;
    // Set value using a string input. Convert using the type_string.
    void set_value_str(const std::string value_string);

    std::string get_category() const { return m_category; }
    std::string get_type() const { return m_paramvalue.type_string(); }



    void set_paramvalue(const NOMAD::ParamValue paramvalue);

    bool value_is_const() const { return m_value_is_const; }

    // Validate the string as a parameter name
    static bool name_is_valid(const std::string &name);
    // Validate the paramvalue
    static bool value_is_valid(const NOMAD::ParamValue &paramvalue);

    // Comparison operator for insertion in set
    bool operator< (const NOMAD::Param &p) const;
};

#include "nomad_nsend.hpp"

#endif
