/**
 \file   Vector.cpp
 \brief  Custom class for vectors (implementation)
 \author Viviane Rochon Montplaisir
 \date   April 2017
 \see    Vector.hpp
 */
#include <math.h>

#include "Vector.hpp"

/*-----------------------------------------------------------*/
/*                        Constructors                       */
/*-----------------------------------------------------------*/
NOMAD::Vector::Vector ( const NOMAD::Point& initialPoint, const NOMAD::Point& endPoint )
  : _initialPoint(initialPoint),
    _endPoint(endPoint)
{
    if (initialPoint.get_size() != endPoint.get_size())
        throw NOMAD::Exception( "Vector.cpp",  __LINE__ ,
                                "NOMAD::Vector::Vector(): Initial and End point sizes mismatch" );
}

NOMAD::Vector::Vector ( const NOMAD::Point& endPoint )
  : _initialPoint(NOMAD::Point(endPoint.get_size(), 0)),
    _endPoint(endPoint)
{
}


/*-----------------------------------------------------------*/
/*                        copy constructor                   */
/*-----------------------------------------------------------*/
NOMAD::Vector::Vector ( const NOMAD::Vector & v ) :
_initialPoint (v._initialPoint),
_endPoint (v._endPoint)
{
}

/*-----------------------------------------------*/
/*                    destructor                 */
/*-----------------------------------------------*/
NOMAD::Vector::~Vector ( void )
{
}

/*-----------------------------------------------------------*/
/*                     affectation operator                  */
/*-----------------------------------------------------------*/
const NOMAD::Vector & NOMAD::Vector::operator = ( const NOMAD::Vector & v )
{
    _initialPoint   = v._initialPoint;
    _endPoint       = v._endPoint;

    return *this;
}

/*-----------------------------------------------------------*/
/*                     class methods                         */
/*-----------------------------------------------------------*/
NOMAD::Double NOMAD::Vector::norm () const
{
    NOMAD::Double norm = 0;

    // VRM: see notes in hpp file. Subject to change.
    // An idea would be to initialize the norm to undefined, and then keep it
    // into a member variable. But we need to make sure to update it if the
    // vector changes (ex. scalar multiplication).
    //

    int size = _endPoint.get_size();

    for (int i = 0; i < size; i++)
    {
        NOMAD::Double diff = _endPoint[i]-_initialPoint[i];
        norm += diff * diff;
    }
    norm = sqrt(norm.todouble());

    return norm;
}





