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

