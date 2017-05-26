/**
 \file   utils.cpp
 \brief  Utility functions
 \author Sebastien Le Digabel, modified by Viviane Rochon Montplaisir
 \date   March 2017
 \see    utils.hpp
 */
#include "utils.hpp"

/*-----------------------------------------------------------------*/
/*                         NOMAD::itos                             */
/*-----------------------------------------------------------------*/
std::string NOMAD::itos ( const int i )
{
    std::ostringstream oss;
    oss << i;
    return oss.str();
}

/*-----------------------------------------------------------------*/
/*                         NOMAD::itos                             */
/*-----------------------------------------------------------------*/
std::string NOMAD::itos ( const size_t i )
{
    std::ostringstream oss;
    oss << i;
    return oss.str();
}


/*-----------------------------------------------------------------*/
/*                         NOMAD::toupper - 1/2                    */
/*-----------------------------------------------------------------*/
void NOMAD::toupper ( std::string & s )
{
    size_t ns = s.size();
    for ( size_t i = 0 ; i < ns ; ++i )
        s[i] = std::toupper(s[i]);
}

/*-----------------------------------------------------------------*/
/*                         NOMAD::toupper - 2/2                    */
/*-----------------------------------------------------------------*/
void NOMAD::toupper ( std::list<std::string> & ls )
{
    std::list<std::string>::iterator       it;
    std::list<std::string>::const_iterator end = ls.end();
    for ( it = ls.begin() ; it != end ; ++it )
        NOMAD::toupper ( *it );
}

/*-----------------------------------------------------------------*/
/*                             NOMAD::atoi                         */
/*-----------------------------------------------------------------*/
bool NOMAD::atoi ( const std::string & s , int & i )
{
    i = -1;
    if ( s.empty() )
        return false;
    
    size_t n = s.size();
    
    if ( s[0] == '-' )
    {
        if ( n > 1 && s[1] == '-' )
            return false;
        std::string ss = s;
        ss.erase(ss.begin());
        if ( NOMAD::atoi ( ss , i ) )
        {
            i = -i;
            return true;
        }
        return false;
    }
    
    for ( size_t k = 0 ; k < n ; ++k )
        if ( !isdigit(s[k]) )
            return false;
    i = std::atoi(s.c_str());
    return true;
}

bool NOMAD::atoi ( const char c , int & i )
{
    std::string s = "-";
    s[0] = c;
    return NOMAD::atoi(s,i);
}


