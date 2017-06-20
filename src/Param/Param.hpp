
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
    NOMAD::ParamValue   m_paramvalue;   // Type could be std::string,
                                        // NOMAD::Double, bool, etc.
    std::string         m_category;     // ALGO, PROBLEM, RUNNER, USER
    bool                m_value_is_const;   // If we can modify this parameter's value

    void    init();

public:
    // Constructor from strings
    Param(std::string param_name,
          std::string value_string,         // String representing parameter value
          std::string type_string,          // String representing parameter type
                                            // Could be "std::string", "NOMAD::Double", etc.
          std::string category = "USER",
          bool value_is_const = false);

    // Constructor with ParamValue
    Param(std::string param_name,
          ParamValue paramvalue,
          std::string category = "USER",
          bool value_is_const = false);

    // Destructor
    ~Param() {}

    // Get/Set

    // Name - Setting name has some validation.
    std::string get_name() const;
    void set_name(const std::string param_name);

    // Get Category
    std::string         get_category()          const { return m_category; }

    // Get for all supported value types
    std::string     get_value_str()     const { return m_paramvalue.get_value_str(); }
    NOMAD::Double   get_value_double()  const { return m_paramvalue.get_value_double(); }
    bool            get_value_bool()    const { return m_paramvalue.get_value_bool(); }
    int             get_value_int()     const { return m_paramvalue.get_value_int(); }
    std::string     get_type_str()      const { return m_paramvalue.get_type_str(); }

    // Set value
    void            set_value (const std::string value);
    void            set_value (const char* value);
    void            set_value (const NOMAD::Double value);
    void            set_value (const double value);
    void            set_value (const bool value);
    void            set_value (const int value);
    // Set value without verifying type. Input is a string.
    void            set_value_str (const std::string value);

    // Get/Set value_is_const
    bool value_is_const() const { return m_value_is_const; }
    void            set_value_is_const( const bool is_const ) { m_value_is_const = is_const; }


    // Validate the string as a parameter name
    static bool name_is_valid(const std::string &param_name);

    // Comparison operator for insertion in set
    bool operator< (const NOMAD::Param &p) const;
};

#include "nomad_nsend.hpp"

#endif
