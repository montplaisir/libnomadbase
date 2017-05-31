/**
 \file   fileutils.cpp
 \brief  Utility functions for files
 \author Viviane Rochon Montplaisir
 \date   June 2017
 \see    fileutils.hpp
 */
#include "fileutils.hpp"

/*-----------------------------------------------------------------*/
/*              check if a file exists and is executable           */
/*-----------------------------------------------------------------*/
bool NOMAD::check_exe_file ( const std::string & file_name )
{
#ifdef WINDOWS
    // don't check on Windows:
    return true;
#else
    return ( access ( file_name.c_str() , X_OK ) == 0 );
#endif
}

/*-----------------------------------------------------------------*/
/*              check if a file exists and is readable             */
/*-----------------------------------------------------------------*/
bool NOMAD::check_read_file ( const std::string & file_name )
{
#ifdef _MSC_VER
    return ( _access ( file_name.c_str() , 4 ) == 0 );
#else
    return ( access ( file_name.c_str() , R_OK ) == 0 );
#endif
}

// Get current directory.
std::string NOMAD::curdir()
{
    char dirbuff[1024];
#ifdef WINDOWS
#include <direct.h>
    _getcwd(dirbuff, 1024);
#else
#include <unistd.h>
    getcwd(dirbuff, 1024);
#endif
    std::string dir(dirbuff);

    return dir;
}

// Extract directory from the given filename.
// If there is no directory, return current directory using getcwd().
std::string NOMAD::dirname( const std::string &filename )
{
    std::string dir = "";

    size_t k = filename.find_last_of ( NOMAD::DIR_SEP );
    if ( k < filename.size() )
    {
        dir = filename.substr (0,k) + NOMAD::DIR_SEP;
    }
    else
    {
        
        dir = std::string(".") + NOMAD::DIR_SEP;
    }

    return dir;
}

// If filename has a path, leave it.
// If it doesn't, add dirname() to it.
std::string NOMAD::fullpath( const std::string &filename )
{
    std::string full = "";

    size_t k = filename.find_last_of ( NOMAD::DIR_SEP );
    if ( k < filename.size() )
        full = filename;
    else
        full = NOMAD::dirname(filename) + filename;

    return full;
}

// Input a line (from a parameters file).
// Remove comments starting with '#'.
// Replace tabs by spaces.
// Trim extra spaces.
void NOMAD::remove_comments( std::string &line )
{
    // Remove comments
    size_t comment_start = line.find('#');
    size_t line_size = line.size();
    if (comment_start < line_size)
    {
        line.replace(comment_start, line_size-comment_start, "");
    }
    line_size = line.size(); // new line size

    // Remove tabs
    size_t tab_index = line.find('\t');
    while (tab_index != std::string::npos)
    {
        //std::cout << "VRM: tab_index = " << tab_index << " line_size = " << line_size << std::endl;
        line.replace(tab_index, 1, " ");
        tab_index = line.find('\t');
    }

    // Trim extra spaces at the beginning
    size_t space_index = line.find(' ');
    while (0 == space_index && line_size > 0)
    {
        //std::cout << "VRM: space_index = " << space_index << " line_size = " << line_size << std::endl;
        //std::cout << "VRM: line = " << line << std::endl;
        line.replace(0, 1, "");
        space_index = line.find(' ');
        line_size = line.size();
    }
    // Trim extra spaces at the end
    size_t space_rindex = line.rfind(' ');
    while (line_size-1 == space_rindex && line_size > 0)
    {
        //std::cout << "VRM: space_rindex = " << space_rindex << " line_size = " << line_size << std::endl;
        line.replace(space_rindex, 1, "");
        space_rindex = line.rfind(' ');
        line_size = line.size();
    }
    // Trim extra spaces in the middle
    size_t two_space_index = line.find("  ");
    while (two_space_index != std::string::npos)
    {
        line.replace(two_space_index, 2, " ");
        two_space_index = line.find("  ");
    }

}
    




