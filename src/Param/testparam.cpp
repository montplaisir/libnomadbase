
// VRM it would be better to use unit tests here! 

#include "Param.hpp"
#include "Parameters.hpp"
using namespace std;

#include <vector>

bool add_param(std::vector<Param> &list, const std::string name, const ParamValue value)
{
    try
    {
        Param p(name, value);
        list.push_back(p);
    }
    catch ( std::exception & e )
    {
        cerr << "Exception thrown: " << e.what() << endl;
        cerr << "Param with name = " << name << " and value = " << value << " not created." << endl;
        cout << "List has " << list.size() << " items." << endl << endl;
        return false;
    }
    cout << "List has " << list.size() << " items." << endl << endl;
    return true;
}



int test_name_validity()
{
    // Test name validity
    cout << "Test parameter names:" << endl;
    std::string s("NAME1_");
    cout << "Name \"" << s << "\" is valid: " << Param::name_is_valid(s) << endl;
    s = "Name2";
    cout << "Name \"" << s << "\" is valid: " << Param::name_is_valid(s) << endl;
    s = "NAME3";
    cout << "Name \"" << s << "\" is valid: " << Param::name_is_valid(s) << endl;
    s = "NAME 4";
    cout << "Name \"" << s << "\" is valid: " << Param::name_is_valid(s) << endl;
    s = "NAME_5";
    cout << "Name \"" << s << "\" is valid: " << Param::name_is_valid(s) << endl;
    s = "NAME_6_IS4TESTING";
    cout << "Name \"" << s << "\" is valid: " << Param::name_is_valid(s) << endl;

    return 0;
}

int test_parameter()
{
    // Test parameter class... this should be moved with other unit tests.
    cout << "Create a list of parameters" << endl;
    std::vector<Param> list;

    cout << "Create a parameter with a valid name and value" << endl;
    std::string name1 = "NAME1";
    NOMAD::Double value1 = NOMAD::Double(1.111);
    add_param(list, name1, value1);

    cout << "Create a parameter with an invalid name (fail)" << endl;
    std::string name2 = "NAME 2";
    double value2 = 2.2;
    add_param(list, name2, value2);

    cout << "Create a parameter with an invalid value (fail)" << endl;
    std::string name3 = "NAME3";
    NOMAD::Double value3 = NOMAD::Double();
    add_param(list, name3, value3);

    cout << "Create 3 more valid parameters" << endl;
    std::string name4 = "NAME_4";
    double value4 = 4.4;
    add_param(list, name4, value4);

    std::string name5 = "NAME_5";
    bool value5 = true;
    add_param(list, name5, value5);

    std::string name6 = "NAME_6";
    NOMAD::Double value6 = 6.6;
    add_param(list, name6, value6);

    cout << "Create a parameter with a name that already exists (success)" << endl;
        // (such management of parameters is outside of the Param class)
    std::string name7 = "NAME_6";
    double value7 = 7.7;
    Param p7(name7, value7);  // Verify that we can construct a parameter using double
    list.push_back(p7);
    cout << "List has " << list.size() << " items." << endl << endl;

    cout << "Create a value of invalid type (fail)" << endl;
    std::string name8 = "NAME_8";
    std::string value8("foo");

    //add_param(list, name8, value8); // VRM does not compile
    //Param p(name8, value8);  // VRM does not compile

    cout << "Try to change a const parameter value (fail)" << endl;
    std::string name9 = "NAME_9";
    NOMAD::Double value9(9.9);
    bool value9_is_const = true;
    Param p9(name9, value9, "TOTO", value9_is_const);
    try
    {
        p9.set_value(0.99999);
    }
    catch ( std::exception & e )
    {
        cerr << "Exception thrown: " << e.what() << endl;
    }
    cout << "\t" << p9.get_name() << "\t" << p9.get_value() << endl << endl;

    cout << "Try to change a non-const parameter value (success) - should be 0.12345" << endl;
    std::string name10 = "NAME_10";
    ParamValue value10(10.101);
    bool value10_is_const = false;
    Param p10(name10, value10, "TOTO", value10_is_const);
    cout << "before:\t" << p10.get_name() << "\t" << p10.get_value() << endl;
    try
    {
        p10.set_value(0.12345);
    }
    catch ( std::exception & e )
    {
        cerr << "Exception thrown: " << e.what() << endl;
    }
    cout << "after:\t" << p10.get_name() << "\t" << p10.get_value() << endl << endl;

    cout << "Try to set value to a double - should be 0.2468" << endl;
    std::string name11 = "NAME_11";
    NOMAD::Double value11 = 0.2468;
    Param p11(name11, value11);
    cout << "\t" << p11.get_name() << "\t" << p11.get_value() << endl << endl;

    cout << "Verify name is converted to caps" << endl;
    std::string name12 = "Name_12";
    double value12 = 0;
    add_param(list, name12, value12);

    cout << "List parameters with their names and values" << endl;
    for (std::vector<Param>::iterator it = list.begin(); it != list.end(); it++)
    {
        cout << "\t" << it->get_name() << "\t" << it->get_value() << endl;
    }
    return 0;
}

int test_parameters()
{
    Parameters all_parameters = Parameters();
    Param p1("first_parameter", 1.1);
    bool inserted = all_parameters.add(p1);
    cout << "Param inserted: " << inserted << endl;

    // Read parameters from a file
    try
    {
        all_parameters.read_from_file("mads_3.8.Dev.txt");
    }
    catch ( std::exception & e )
    {
        cerr << "Exception thrown: " << e.what() << endl;
    }

/*
    // Output parameters to a file
    try
    {
        all_parameters.write_to_file("");
    }
    catch ( std::exception & e )
    {
        cerr << "Exception thrown: " << e.what() << endl;
    }
*/
    return 0;
}


int main()
{
    //test_name_validity();
    //test_parameter();
    test_parameters();
}
