/**
 \file   fileutils.hpp
 \brief  Utility functions about files (headers)
 \author Viviane Rochon Montplaisir
 \date   June 2017
 \see    fileutils.cpp
 */
#ifndef __NOMAD400_FILEUTILS__
#define __NOMAD400_FILEUTILS__

// use of 'access' or '_access', and getpid() or _getpid():
#ifdef _MSC_VER
#include <io.h>
//#include <process.h>
#else
#include <unistd.h>
#endif

#include "Util/defines.hpp"

#include "nomad_nsbegin.hpp"
    
    // Copied from NOMAD_3.
    /// Check if a file exists and is executable.
    /**
     \param file_name A string corresponding to a file name -- \b IN.
     \return          A boolean equal to \c true if the file is executable.
     */
    bool check_exe_file  ( const std::string & file_name );

    /// Check if a file exists and is readable.
    /**
     \param file_name A string corresponding to a file name -- \b IN.
     \return          A boolean equal to \c true if the file exists and is readable.
     */
    bool check_read_file ( const std::string & file_name );

    /// Check if a file exists and is writable.
    /**
     \param file_name A string corresponding to a file name -- \b IN.
     \return          A boolean equal to \c true if the file exists and is writable.
     */
    bool check_write_file ( const std::string & file_name );

    // Get current directory
    std::string curdir();

    // Extract directory from the given filename.
    // If there is no directory, return ".".
    std::string dirname( const std::string &filename );

    // If filename has a path, leave it.
    // If it doesn't, add dirname() to it.
    std::string fullpath( const std::string &filename );

    // Input a line (from a parameters file).
    // Remove comments starting with '#'.
    // Replace tabs by spaces.
    // Trim extra spaces.
    void remove_comments( std::string &line );

    
#include "nomad_nsend.hpp"

#endif
