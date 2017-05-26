/**
 \file   Exception.hpp
 \brief  Custom class for exceptions (headers)
 \author Sebastien Le Digabel
 \date   2010-03-29
 \see    Exception.cpp
 */
#ifndef __NOMAD400_EXCEPTION__
#define __NOMAD400_EXCEPTION__

#include <sstream>

#include "nomad_nsbegin.hpp"
    
    /// Custom class for exceptions.
    /**
     NOMAD uses this type of exceptions.
     It indicates the file and line number at which a throw is made.
     
     \b Example
     
     \code
     throw NOMAD::Exception ( __FILE__ , __LINE__ , "an error message" );
     \endcode
     */
    class Exception : public std::exception {
        
    private:
        
        mutable std::string _what;  ///< Error message.
        std::string         _file;  ///< File where the exception is thrown.
        int                 _line;  ///< Line number at which the exception is thrown.
        
    public:
        
        /// Constructor.
        /**
         \param file A string corresponding to the file where the
         exception is thrown -- \b IN
         \param line An integer corresponding to the line number
         at which the exception is thrown -- \b IN.
         \param msg  A string corresponding to the error message -- \b IN.
         */
        Exception ( const std::string & file , const int line , const std::string & msg )
        : _what ( msg  ) ,
        _file ( file ) ,
        _line ( line )   {}
        
        /// Destructor.
        virtual ~Exception ( void ) throw() {}
        
        /// Access to the error message.
        /**
         \return A string with the error message.
         */
        const char * what ( void ) const throw();
    };
#include "nomad_nsend.hpp"

#endif
