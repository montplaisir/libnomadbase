
#ifndef __RUNNER400_PARAM__
#define __RUNNER400_PARAM__

#include <string>

#include <Util/Exception.hpp>

#include "ParamValue.hpp"

// Class for all Parameters.


class Param
{
private:
    std::string     _category;  // Ex. ALGO, PROBLEM, ...
    std::string     _name;      // Will be converted to caps
    ParamValue      _value;
    bool            _value_is_const;

    void    init();

public:
    // Constructor
    Param(std::string name, ParamValue value,
              std::string category = std::string(),
              bool value_is_const = true);

    // Destructor
    virtual ~Param() {}

    // Get/Set parameter name and value
    // Setting name has some validation.
    // VRM see if this is the right place to validate.
    std::string get_name() const;
    void set_name(const std::string name);

    ParamValue get_value() const;
    void set_value(const ParamValue value);

    const bool value_is_const() const { return _value_is_const; }

    // Validate the string as a parameter name
    static bool name_is_valid(const std::string &name);
    // Validate the value
    static bool value_is_valid(const ParamValue &value);

    // Comparison operator for insertion in set
    bool operator< (const Param &p) const;
};

#endif
