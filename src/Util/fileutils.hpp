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

    
#include "nomad_nsend.hpp"

#endif
