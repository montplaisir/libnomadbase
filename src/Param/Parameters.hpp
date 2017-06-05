
#ifndef __RUNNER400_PARAMETERS__
#define __RUNNER400_PARAMETERS__

#include <set>
#include <vector>
#include "Param.hpp"


// Manage all parameters.
class Parameters
{
private:
    std::set<Param> m_params;

    static const std::vector<std::string> m_param_categories;

    // For debugging
    void debug_display() const;
public:
    explicit Parameters();
    virtual ~Parameters() {}

    // Add a Param to the list.
    // True if p was correctly added.
    bool add(const Param &p);

    // Get param by name
    bool find(const std::string name, Param &foundparam) const;

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



#endif
