
#ifndef __RUNNER400_PARAMETERS__
#define __RUNNER400_PARAMETERS__

#include <set>
#include <vector>
#include "Param.hpp"

#include "nomad_nsbegin.hpp"

// Manage all parameters.
class Parameters
{
private:
    std::set<NOMAD::Param> m_params;

    static const std::vector<std::string> m_param_categories;

    // For debugging
    void debug_display() const;
public:
    explicit Parameters();
    virtual ~Parameters() {}

    // Add a Param to the list.
    // True if p was correctly added.
    bool add(const NOMAD::Param &p);

    // Update parameter value with new value.
    bool update(NOMAD::Param &p, const std::string value_string);

    // Get param by name
    bool find(const std::string name, NOMAD::Param &foundparam) const;

    // Get/Set
    // Get param value by name. Return value as string.
    std::string get_value_str(const std::string name) const;
    // Get param value, specifying return type.
    template <typename T>
    T get_value(const std::string name) const
    {
        std::set<NOMAD::Param>::const_iterator it;
        for (it = m_params.begin(); it != m_params.end(); it++)
        {
            if (name == it->get_name())
            {
                return it->get_value<T>();
            }
        }
        std::string err = "Parameter is not defined: " + name;
        throw NOMAD::Exception(__FILE__,__LINE__,err);
        return T();
    }

    // Check if a parameter of that name exists.
    bool is_defined(const std::string name) const;

    // Helpers for reader
    static bool is_parameter_category(const std::string s);
    static bool is_runner_param(const std::string line);

    static bool parse_param_4fields(const std::string line,
            std::string &category, std::string &type_string, 
            std::string &name, std::string &value_string);

    static bool parse_param_2fields(const std::string line,
            std::string &name, std::string &value_string);

    // Parse line and add parameter. Yes, this should be 2 methods.
    void parse_line(std::string line);

    // Read parameters from a file and insert them
    void read_from_file(const std::string &filename);

    // Output parameters to a file
    void write_to_file(const std::string &filename) const;
};

#include "nomad_nsend.hpp"


#endif
