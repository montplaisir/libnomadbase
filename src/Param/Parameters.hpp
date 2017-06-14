
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
    // 1 if parameter was updated.
    // 0 if parameter was found, but could not be updated.
    // -1 if parameter was not found.
    // if parameter was updated, false if it
    // was not found or could not be update.
    int update(const std::string param_name, const std::string value_string);

    // Delete a Param from the list, by name.
    // True if Param named param_name was deleted successfully.
    bool remove(const std::string param_name);

    // Return true if a parameter with that name exists, false otherwise.
    bool is_defined(const std::string param_name) const;

    // Get/Set
    // Get param value for all supported value types
    std::string     get_value_str   (const std::string param_name)  const;
    NOMAD::Double   get_value_double(const std::string param_name)  const;
    bool            get_value_bool  (const std::string param_name)  const;
    int             get_value_int   (const std::string param_name)  const;
    std::string     get_type_str    (const std::string param_name)  const;

    // Find parameter with this name
    bool find(const std::string param_name, Param &param) const;

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
