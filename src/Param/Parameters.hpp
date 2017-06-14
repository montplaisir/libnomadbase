
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
    // True if param was correctly added.
    bool add(const NOMAD::Param &param);

    // Update parameter value with new value.
    // Return value:
    // 1 if parameter was update.
    // 0 if parameter was found, but could not be updated.
    // -1 if parameter was not found.
    // if parameter was updated, false if it
    // was not found or could not be update.
    int update(const std::string param_name, const std::string value_string);

    // Delete a Param from the list, by name.
    // True if Param named param_name was deleted successfully.
    bool remove(const std::string param_name);

    // Return true if there exists a parameter with that name, false otherwise.
    bool exists(const std::string param_name) const;

    // Get/Set
    // Get param value by name. Return value as string.
    std::string get_value_str(const std::string param_name) const;
    // Get param value, specifying return type.
    template <typename T>
    T get_value(const std::string param_name) const
    {
        std::set<NOMAD::Param>::const_iterator it;
        for (it = m_params.begin(); it != m_params.end(); it++)
        {
            if (param_name == it->get_name())
            {
                return it->get_value<T>();
            }
        }
        std::string err = "Parameter is not defined: " + param_name;
        throw NOMAD::Exception(__FILE__,__LINE__,err);
        return T();
    }

    // Check if a parameter of that name exists.
    bool is_defined(const std::string param_name) const;

    // Helpers for reader
    static bool is_parameter_category(const std::string s);
    static bool is_runner_param(const std::string line);

    static bool parse_param_4fields(const std::string line,
            std::string &category, std::string &type_string, 
            std::string &param_name, std::string &value_string);

    static bool parse_param_2fields(const std::string line,
            std::string &param_name, std::string &value_string);

    // Parse line and add parameter. Yes, this should be 2 methods.
    void parse_line(std::string line);

    // Read parameters from a file and insert them
    void read_from_file(const std::string &filename);

    // Output parameters to a file
    void write_to_file(const std::string &filename) const;
};

#include "nomad_nsend.hpp"


#endif
