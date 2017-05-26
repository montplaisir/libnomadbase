/**
 \file   defines.hpp
 \brief  Definitions
 \author Sebastien Le Digabel, modified by Viviane Rochon Montplaisir
 \date   March 2017
 */
#ifndef __NOMAD400_DEFINES__
#define __NOMAD400_DEFINES__

#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <limits.h>
#include <cstdlib>


// Define in order to display debug information
//#define DEBUG

// define in order to display memory debug information:
//#define MEMORY_DEBUG

#ifdef DEBUG
#ifndef MEMORY_DEBUG
#define MEMORY_DEBUG
#endif
#endif


// CASE Linux using gnu compiler   
#ifdef __gnu_linux__
#define GCC_X
#endif

// CASE OSX using gnu compiler 
#ifdef __APPLE__
#ifdef __GNUC__
#define GCC_X
#endif
#endif

// CASE minGW using gnu compiler
#ifdef __MINGW32__
#define WINDOWS
#ifdef __GNUC__
#define GCC_X
#endif
#endif

// CASE Visual Studio C++ compiler
#ifdef _MSC_VER
#define WINDOWS
#pragma warning(disable:4996)
#endif

// For NOMAD random number generator 
#if !defined(UINT32_MAX)
typedef unsigned int uint32_t;
#define UINT32_MAX	0xffffffff
#endif

#include "nomad_nsbegin.hpp"
	
	// Directory separator
#ifdef WINDOWS
	const char        DIR_SEP = '\\';           ///< Directory separator
	const std::string HOME    = "%NOMAD_HOME%"; ///< Home directory
#else
	const char        DIR_SEP = '/';            ///< Directory separator
	const std::string HOME    = "$NOMAD_HOME";  ///< Home directory
#endif
	
	/// Maximum number of variables.
	const int MAX_DIMENSION = 1000;
	
	/// Default epsilon used by NOMAD::Double
	/** Use Parameters::set_EPSILON(), or parameter EPSILON,
	 or NOMAD::Double::set_epsilon() to change it
	 */
	const double DEFAULT_EPSILON = 1e-13;
	
	/// Default infinity string used by NOMAD::Double
	/** Use Parameters::set_INF_STR(), or parameter INF_STR,
	 or NOMAD::Double::set_inf_str() to change it
	 */
	const std::string DEFAULT_INF_STR = "inf";
	
	/// Default undefined value string used by NOMAD::Double
	/** Use Parameters::set_UNDEF_STR(), or parameter UNDEF_STR,
	 or NOMAD::Double::set_undef_str() to change it
	 */
	const std::string DEFAULT_UNDEF_STR = "NaN";
    
	const double INF = std::numeric_limits<double>::max(); ///< Infinity
	const double NaN = std::numeric_limits<double>::quiet_NaN(); ///< Quiet Not-A-Number
    const double P_INF_INT = std::numeric_limits<int>::max(); ///< plus infinity for int
    const double M_INF_INT = std::numeric_limits<int>::min(); ///< minus infinity for int
	
	const double D_INT_MAX = UINT32_MAX; ///< The UINT32_MAX constant as a \c double
	
#include "nomad_nsend.hpp"

#endif
