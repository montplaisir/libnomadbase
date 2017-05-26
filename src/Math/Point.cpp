/**
 \file   Point.cpp
 \brief  Custom class for points (implementation)
 \author Sebastien Le Digabel and Viviane Rochon Montplaisir
 \date   March 2017
 \see    Point.hpp
 */
#include "Math/Point.hpp"

// VRM temporary, should be included via other means
#include <iomanip>
using namespace std;

std::ostream& NOMAD::operator<<(std::ostream& out, const NOMAD::Point& point)
{
    point.display(out);
    return out;
}

/*-----------------------------------------------------------*/
/*                         constructor                       */
/*-----------------------------------------------------------*/
NOMAD::Point::Point ( int n , const NOMAD::Double & d )
  : _n (n),
    _coords (NULL)
{
    if (_n > 0)
    {
        _coords = new NOMAD::Double [_n];
        if ( d.is_defined() )
            std::fill ( _coords , _coords+_n , d );
    }
    else
        _n = 0;
}

/*-----------------------------------------------------------*/
/*                        copy constructor                   */
/*-----------------------------------------------------------*/
NOMAD::Point::Point ( const NOMAD::Point & p )
  : _n (p._n),
    _coords (NULL)
{
    if ( _n > 0 )
    {
        NOMAD::Double       * p1 =   _coords = new NOMAD::Double [_n];
        const NOMAD::Double * p2 = p._coords;
        for ( int k = 0 ; k < _n ; ++k , ++p1 , ++p2 )
        {
            *p1 = *p2;
        }
    }
}

/*-----------------------------------------------*/
/*                    destructor                 */
/*-----------------------------------------------*/
NOMAD::Point::~Point ( void )
{
    delete [] _coords;
}

/*-----------------------------------------------------------*/
/*                       '[]' operators                      */
/*-----------------------------------------------------------*/

// const version:
const NOMAD::Double & NOMAD::Point::operator [] ( int i ) const
{
// VRM remettre les Exceptions ici ASP
    return _coords[i];
}

// non-const version:
NOMAD::Double & NOMAD::Point::operator [] ( int i )
{
    return _coords[i];
}

/*-----------------------------------------------------------*/
/*                     affectation operator                  */
/*-----------------------------------------------------------*/
const NOMAD::Point & NOMAD::Point::operator = ( const NOMAD::Point & p )
{
    if ( this == &p )
        return *this;

    if ( _n != p._n )
    {
        delete [] _coords;
        _n = p._n;
        if (_n > 0)
            _coords = new NOMAD::Double [_n];
        else
            _coords = NULL;
    }

    NOMAD::Double       * p1 =   _coords;
    const NOMAD::Double * p2 = p._coords;
    for ( int k = 0 ; k < _n ; ++k , ++p1 , ++p2 )
        *p1 = *p2;

    return *this;
}

/*-----------------------------------------------------------*/
/*                           operator ==                     */
/*-----------------------------------------------------------*/
bool NOMAD::Point::operator == ( const NOMAD::Point & p ) const
{
    if ( this == &p )
        return true;
    if ( p._n != _n )
        return false;

    const NOMAD::Double * p1 =   _coords;
    const NOMAD::Double * p2 = p._coords;
    for ( int k = 0 ; k < _n ; ++k , ++p1 , ++p2 )
        if ( *p1 != *p2 )
            return false;

    return true;
}

/*--------------------------------------------------------------------------*/
/* comparison operator '<': it is used to find and store the points         */
/*                           in the cache/database                          */
/*--------------------------------------------------------------------------*/
bool NOMAD::Point::operator < ( const NOMAD::Point & p ) const
{
    if ( this == &p )
        return false;

    if ( _n < p._n )
        return true;
    if ( _n > p._n )
        return false;

    const NOMAD::Double * p1 =   _coords;
    const NOMAD::Double * p2 = p._coords;

    for ( int k = 0 ; k < _n ; ++k , ++p1 , ++p2 )
    {

        if ( *p1 < *p2 )
            return true;

        if ( *p1 > *p2 )
            return false;
    }

    return false;
}

/*-----------------------------------------------------------*/
/*                             display                       */
/*-----------------------------------------------------------*/
void NOMAD::Point::display ( std::ostream &out,
                            const std::string    & sep ,
                            int                    w   ,
                            int                    lim   ) const
{
    int nm1 = _n-1;

    // for a limited display of maximum lim elements:
    if ( lim > 0 && lim < _n )
    {

        int l1 = (lim + 1) / 2 , l2 = lim / 2 , i;

        // first coordinates:
        for ( i = 0 ; i < l1 ; ++i )
            out << std::setw ( w ) << _coords[i] << sep;

        // separator:
        out << "..." << sep;

        // last coordinates:
        for ( i = _n - l2 ; i < nm1 ; ++i )
            out << std::setw ( w ) << _coords[i] << sep;
    }

    // normal display (lim <= 0 or lim >= _n):
    else
    {
        const NOMAD::Double * p = _coords;
        for ( int i = 0 ; i < nm1 ; ++i , ++p )
            out << std::setw ( w ) << *p << sep;
    }

    // last coordinate (different because there is no separator after that):
    if ( _n > 0 )
        out << std::setw ( w ) << _coords[nm1];
}


