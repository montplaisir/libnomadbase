/**
 \file   utils.hpp
 \brief  Utility functions (headers)
 \author Sebastien Le Digabel, modified by Viviane Rochon Montplaisir
 \date   March 2017
 \see    utils.cpp
 */
#ifndef __NOMAD400_UTILS__
#define __NOMAD400_UTILS__

#include <cmath>
#include <list>

#include "Util/defines.hpp"


#include "nomad_nsbegin.hpp"

    /// Convert a string in {"YES","NO","Y","N","0","1","TRUE","FALSE"} to a boolean.
    /**
     \param s The string -- \b IN.
     \return  An integer equal to \c 0 for \c false, \c 1 for \c true,
     and \c -1 if the conversion failed.
     */
    int string_to_bool ( const std::string & s );
    
    /// Transform an integer into a string.
    /**
     \param i The integer -- \b IN.
     \return  The string.
     */
    std::string itos ( const int i );
    
    /// Transform a unsigned long (size_t) into a string.
    /**
     \param i The unsigned long -- \b IN.
     \return  The string.
     */
    std::string itos ( const size_t i );
    
    /// Put a string into upper cases.
    /**
     \param s The string -- \b IN/OUT.
     */
    void toupper ( std::string & s );
    
    /// Put a list of strings into upper cases.
    /**
     \param ls The list of strings -- \b IN/OUT.
     */
    void toupper  ( std::list<std::string> & ls );
    
    /// Convert a string into an integer.
    /**
     \param s The string  -- \b IN.
     \param i The integer -- \b OUT.
     \return  A boolean equal to \c true if the conversion was possible.
     */
    bool atoi ( const std::string & s , int & i );
    
    /// Convert a character into an integer.
    /**
     \param c The character -- \b IN.
     \param i The integer   -- \b OUT.
     \return  A boolean equal to \c true if the conversion was possible.
     */
    bool atoi ( const char c , int & i );
    
#include "nomad_nsend.hpp"

#endif
