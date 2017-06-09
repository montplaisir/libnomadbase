/**
 \file   Double.cpp
 \brief  Custom class for double-precision reals (implementation)
 \author Sebastien Le Digabel
 \date   2010-04-02
 \see    Double.hpp
 */
#include "Math/Double.hpp"
#include <boost/lexical_cast.hpp>

/*-----------------------------------*/
/*   static members initialization   */
/*-----------------------------------*/
double      NOMAD::Double::_epsilon         = NOMAD::DEFAULT_EPSILON;
std::string NOMAD::Double::_inf_str         = NOMAD::DEFAULT_INF_STR;
std::string NOMAD::Double::_undef_str       = NOMAD::DEFAULT_UNDEF_STR;
#ifdef MEMORY_DEBUG
int         NOMAD::Double::_cardinality     = 0;
int         NOMAD::Double::_max_cardinality = 0;
#endif

/*-----------------------------------------------*/
/*                  constructor 1                */
/*-----------------------------------------------*/
NOMAD::Double::Double ( void )
: _value   ( 0.0   ) ,
_defined ( false )
{
#ifdef MEMORY_DEBUG
    ++NOMAD::Double::_cardinality;
    if ( NOMAD::Double::_cardinality > NOMAD::Double::_max_cardinality )
        ++NOMAD::Double::_max_cardinality;
#endif
}

/*-----------------------------------------------*/
/*                  constructor 2                */
/*-----------------------------------------------*/
NOMAD::Double::Double ( double v )
: _value   ( v    ) ,
_defined ( true )
{
#ifdef MEMORY_DEBUG
    ++NOMAD::Double::_cardinality;
    if (NOMAD::Double::_cardinality > NOMAD::Double::_max_cardinality)
        ++NOMAD::Double::_max_cardinality;
#endif
}

/*-----------------------------------------------*/
/*                  Copy constructor             */
/*-----------------------------------------------*/
NOMAD::Double::Double ( const NOMAD::Double & d )
: _value   ( d._value   ) ,
_defined ( d._defined )
{
#ifdef MEMORY_DEBUG
    ++NOMAD::Double::_cardinality;
    if (NOMAD::Double::_cardinality > NOMAD::Double::_max_cardinality)
        ++NOMAD::Double::_max_cardinality;
#endif
}

/*-----------------------------------------------*/
/*                    destructor                 */
/*-----------------------------------------------*/
NOMAD::Double::~Double ( void )
{
#ifdef MEMORY_DEBUG
    --NOMAD::Double::_cardinality;
#endif
}

/*-----------------------------------------------*/
/*               set epsilon (static)            */
/*-----------------------------------------------*/
void NOMAD::Double::set_epsilon ( double eps )
{
    if ( eps <= 0.0 )
        throw NOMAD::Exception ( "Double.cpp" , __LINE__ ,
                                "NOMAD::Double::set_epsilon(): invalid epsilon" );
    NOMAD::Double::_epsilon = eps;
}

/*-----------------------------------------------*/
/*                  get the value                */
/*-----------------------------------------------*/
const double & NOMAD::Double::todouble ( void ) const
{
    if ( !_defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double::todouble(): value not defined" );
    return _value;
}

/*-----------------------------------------------*/
/*          get the value as a string            */
/*-----------------------------------------------*/
const std::string NOMAD::Double::tostring ( void ) const
{
    std::string ret_str;

    if ( _defined )
    {
        if ( _value == NOMAD::INF )
            ret_str = NOMAD::Double::_inf_str;
        else if ( _value == -NOMAD::INF )
            ret_str = "-" + NOMAD::Double::_inf_str;
        else
        {
            std::stringstream ss;
            ss << _value;
            ret_str = ss.str();
        }
    }
    else
    {
        ret_str = NOMAD::Double::_undef_str;
    }

    return ret_str;

}

/*------------------------------------------*/
/*                    input                 */
/*------------------------------------------*/
std::istream & NOMAD::operator >> ( std::istream & in , NOMAD::Double & d )
{
    std::string s;
    in >> s;
    
    if ( !in.fail() && !d.atof (s) )
        in.setstate ( std::ios::failbit );
    
    return in;
}

/*-----------------------------------------------*/
/*      atof: value determined by a string       */
/*-----------------------------------------------*/
bool NOMAD::Double::atof ( const std::string & ss )
{
    
    std::string s = ss;
    NOMAD::toupper(s);
    
    if ( s == "-" || ss == NOMAD::Double::_undef_str )
    {
        _value   = 0.0;
        _defined = false;
        return true;
    }
    
    if ( s == "INF" ||  s == "+INF" ||
        ss == NOMAD::Double::_inf_str ||
        ss == ("+" + NOMAD::Double::_inf_str) )
    {
        _value   = NOMAD::INF;
        _defined = true;
        return true;
    }
    
    if ( s == "-INF" || ss == ("-" + NOMAD::Double::_inf_str) )
    {
        _value   = -NOMAD::INF;
        _defined = true;
        return true;
    }
    
    if ( s.empty() || (s.size() == 1 && !isdigit(s[0])) )
        return false;
    
    if ( !isdigit(s[0]) && s[0] != '+' && s[0] != '-' && s[0] != '.' )
        return false;
    
    size_t n = s.size();
    for ( size_t k = 1 ; k < n ; ++k )
        if ( !isdigit(s[k]) && s[k] != '.' )
        {
            if ( s[k] == 'E' )
            {
                if ( s.size() == k+1 )
                    return false;
                ++k;
                if ( !isdigit(s[k]) && s[k] != '+' && s[k] != '-' )
                    return false;
            }
            else
                return false;
        }
    
    *this = std::atof ( s.c_str() );
    return true;
}

/*-------------------------------------------------*/
/*  atof from a string that can begin with 'r' to  */
/*  indicate a proportion (relative value)         */
/*-------------------------------------------------*/
bool NOMAD::Double::relative_atof ( const std::string & s , bool & relative )
{
    if ( std::toupper(s[0]) == 'R' )
    {
        relative  = true;
        std::string ss = s;
        ss.erase(ss.begin());
        if ( !atof(ss) )
            return false;
        return ( *this >= 0.0 );
    }
    relative = false;
    return atof(s);
}

/*-----------------------------------------------*/
/*            is the value an integer?           */
/*-----------------------------------------------*/
bool NOMAD::Double::is_integer ( void ) const
{
    if ( !_defined )
        return false;
    return ( NOMAD::Double(std::floor(_value))) == ( NOMAD::Double(std::ceil(_value)) );
}

/*-----------------------------------------------*/
/*             is the value binary ?             */
/*-----------------------------------------------*/
bool NOMAD::Double::is_binary ( void ) const
{
    if ( !_defined )
        return false;
    return ( NOMAD::Double(_value) == 0.0 || NOMAD::Double(_value) == 1.0 );
}

/*-------------------------------------*/
/*               d = d1/d2             */
/*-------------------------------------*/
const NOMAD::Double NOMAD::operator / ( const NOMAD::Double & d1 ,
                                       const NOMAD::Double & d2   )
{
    if ( d2.todouble() == 0.0 )
        throw NOMAD::Double::Invalid_Value ( "Double.cpp" , __LINE__ ,
                                            "NOMAD::Double: d1 / d2: division by zero" );
    return NOMAD::Double ( d1.todouble() / d2.todouble() );
}

/*-------------------------------------*/
/*                d1 += d2             */
/*-------------------------------------*/
const NOMAD::Double & NOMAD::Double::operator += ( const NOMAD::Double & d2 )
{
    if ( !_defined || !d2._defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double: d1 += d2: d1 or d2 not defined" );
    _value += d2._value;
    return *this;
}

/*-------------------------------------*/
/*               d1 -= d2              */
/*-------------------------------------*/
const NOMAD::Double & NOMAD::Double::operator -= ( const NOMAD::Double & d2 )
{
    if ( !_defined || !d2._defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double: d1 -= d2: d1 or d2 not defined" );
    _value -= d2._value;
    return *this;
}

/*-------------------------------------*/
/*                d1 *= d2             */
/*-------------------------------------*/
const NOMAD::Double & NOMAD::Double::operator *= ( const NOMAD::Double & d2 )
{
    if ( !_defined || !d2._defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double: d1 *= d2: d1 or d2 not defined" );
    _value *= d2._value;
    return *this;
}

/*-------------------------------------*/
/*               d1 /= d2              */
/*-------------------------------------*/
const NOMAD::Double & NOMAD::Double::operator /= ( const NOMAD::Double & d2 )
{
    if ( !_defined || !d2._defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double: d1 /= d2: d1 or d2 not defined" );
    if ( d2._value == 0.0 )
        throw Invalid_Value ( "Double.cpp" , __LINE__ ,
                             "NOMAD::Double: d1 /= d2: division by zero" );
    _value /= d2._value;
    return *this;
}

/*-------------------------------------*/
/*                  ++d                */
/*-------------------------------------*/
NOMAD::Double & NOMAD::Double::operator++ ( void )
{
    if ( !_defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ , "NOMAD::Double: ++d: d not defined" );
    _value += 1;
    return *this;
}

/*-------------------------------------*/
/*                  d++                */
/*-------------------------------------*/
NOMAD::Double NOMAD::Double::operator++ ( int n )
{
    if ( !_defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ , "NOMAD::Double: d++: d not defined" );
    NOMAD::Double tmp = *this;
    if( n <= 0 )
        n = 1;
    _value += n;
    return tmp;
}

/*-------------------------------------*/
/*                --d                  */
/*-------------------------------------*/
NOMAD::Double & NOMAD::Double::operator-- ( void )
{
    if ( !_defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ , "NOMAD::Double: --d: d not defined" );
    _value -= 1;
    return *this;
}

/*-------------------------------------*/
/*                  d--                */
/*-------------------------------------*/
NOMAD::Double NOMAD::Double::operator-- ( int n )
{
    if ( !_defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double: d--: d not defined" );
    NOMAD::Double tmp = *this;
    if ( n <= 0 )
        n = 1;
    _value -= n;
    return tmp;
}

/*-------------------------------------*/
/*              operators =            */
/*-------------------------------------*/
NOMAD::Double & NOMAD::Double::operator = ( const NOMAD::Double & d )
{
    _value   = d._value;
    _defined = d._defined;
    return *this;
}

NOMAD::Double & NOMAD::Double::operator = ( double r )
{
    _value   = r;
    _defined = true;
    return *this;
}

/*------------------------------------------*/
/*                  display                 */
/*------------------------------------------*/
/*
void NOMAD::Double::display ( ) const
{
    std::ostream &out = std::cout;  // VRM to be generalized, this value should be fetched
                                    // in a manager singleton
    if ( _defined )
    {
        if ( _value == NOMAD::INF )
            out << NOMAD::Double::_inf_str;
        else if ( _value == -NOMAD::INF )
            out << "-" << NOMAD::Double::_inf_str;
        else if ( std::floor(_value) == std::ceil(_value) && fabs(_value) < INT_MAX-1 )
            out << static_cast<int>(_value);
        else
            out << _value;
    }
    else
        out << NOMAD::Double::_undef_str;
}
*/

/*------------------------------------------*/
/*              display with format         */
/*------------------------------------------*/
/*
void NOMAD::Double::display ( const std::string    & format   ) const
{
    // VRM TODO copy from version 3, with adjustments
}
*/

#include "nomad_nsbegin.hpp"
std::ostream& operator<< ( std::ostream& os, const NOMAD::Double& d )
{
    if ( d.is_defined() )
    {
        double value = d.todouble();
        if ( value == NOMAD::INF )
            os << NOMAD::Double::get_inf_str();
        else if ( value == -NOMAD::INF )
            os << "-" << NOMAD::Double::get_inf_str();
        else if ( std::floor(value) == std::ceil(value) && fabs(value) < INT_MAX-1 )
            os << static_cast<int>(value);
        else
            os << value;
    }
    else
        os << NOMAD::Double::get_undef_str();

    return os;
}
#include "nomad_nsend.hpp"

/*------------------------------------------*/
/*                round to int              */
/*------------------------------------------*/
int NOMAD::Double::round ( void ) const
{
    if ( !_defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double::round(): value not defined" );
    
    double d = (_value < 0.0 ? -std::floor(.5-_value) : std::floor(.5+_value));
  
    if ( d > NOMAD::P_INF_INT || d < NOMAD::M_INF_INT )
        throw Invalid_Value ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double::round(): value cannot be rounded to integer because it is outside of range" );

    return static_cast<int> (d);
}

/*------------------------------------------*/
/*              round to double             */
/*------------------------------------------*/
const NOMAD::Double NOMAD::Double::roundd ( void ) const
{
    if ( !_defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double::round(): value not defined" );

    return (_value < 0.0 ? -std::floor(.5-_value) : std::floor(.5+_value));
    
}


/*------------------------------------------*/
/*                  Ceil                  */
/*------------------------------------------*/
const NOMAD::Double NOMAD::Double::ceil ( void ) const
{
    if ( !_defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double::ceil(): value not defined" );
    return NOMAD::Double( std::ceil(_value) );
}

/*------------------------------------------*/
/*                  Floor                  */
/*------------------------------------------*/
const NOMAD::Double NOMAD::Double::floor ( void ) const
{
    if ( !_defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double::floor(): value not defined" );
    return NOMAD::Double( std::floor(_value) );
}

/*------------------------------------------*/
/*                    abs                   */
/*------------------------------------------*/
const NOMAD::Double NOMAD::Double::abs ( void ) const
{
    if ( !_defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double::abs(): value not defined" );
    return fabs ( _value );
}

/*------------------------------------------*/
/*                  square                  */
/*------------------------------------------*/
const NOMAD::Double NOMAD::Double::pow2 ( void ) const
{
    if ( !_defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double::pow2(): value not defined" );
    return pow ( _value , 2 );
}

/*------------------------------------------*/
/*                square root               */
/*------------------------------------------*/
const NOMAD::Double NOMAD::Double::sqrt ( void ) const
{
    if ( !_defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double::sqrt(): value not defined" );
    if ( *this < 0.0 )
        throw NOMAD::Double::Invalid_Value ( "Double.cpp" , __LINE__ ,
                                            "NOMAD::Double::sqrt(x): x < 0" );
    
    return std::sqrt ( _value );
}

/*---------------------------------------------*/
/*  relative error with another NOMAD::Double  */
/*---------------------------------------------*/
//
// This error computation is based on:
//
// A. Ziv. Relative distance–an error measure in round-off error analysis. Mathematics
// of Computation, 39(160):563–569, 1982. doi:10.1090/S0025-5718-1982-0669649-2.
//
// The error will be in [0;2]
//
// Modified: 2014-06-07, S. Le Digabel
//
const NOMAD::Double NOMAD::Double::rel_err ( const Double & x ) const
{
    if ( !_defined || !x._defined )
        throw Not_Defined ( "Double.cpp" , __LINE__ ,
                           "NOMAD::Double::rel_err(): one of the values is not defined" );
    
    // 1. test if x==y:
    if ( this == &x || _value == x._value )
        return 0.0;
    
    double diff = fabs ( _value - x._value );
    
    // 2. test if one of the values is zero:
    if ( _value == 0.0 || x._value == 0.0 )
    {
        
        // we return min{2,|x-y|} (instead of 1):
        if ( diff > 2.0 )
            return 2.0;
        return diff;
    }
    
    // 3. compute the original error:
    double a   = fabs ( _value   );
    double b   = fabs ( x._value );
    double err = diff / ( (a<b) ? b : a );
    
    // 4. test if we have opposite signs:
    if ( _value * x._value < 0.0 )
    {
        
        // the original error gives err in ]1;2] : we check if |x-y| < 1
        // and if so we return |x-y| :
        if ( diff < 1.0 )
            return diff;
    }
    
    // we return the original error:
    return err;
}


/*---------------------------------------------------------------------*/
/*  the same as operator < but with consideration of undefined values  */
/*---------------------------------------------------------------------*/
bool NOMAD::Double::comp_with_undef ( const NOMAD::Double & d ) const
{
    if ( this == &d )
        return false;
    
    bool d1d = is_defined();
    bool d2d = d.is_defined();
    
    if ( !d1d && !d2d )
        return false;
    
    if ( !d1d )
        return true;
    
    if ( !d2d )
        return false;
    
    return ( *this < d );
}

/*------------------------------------*/
/*  projection to mesh of size delta  */
/*  ( *this = ref + k * delta )       */
/*------------------------------------*/
void NOMAD::Double::project_to_mesh ( const NOMAD::Double & ref   ,
                                     const NOMAD::Double & delta ,
                                     const NOMAD::Double & lb    ,
                                     const NOMAD::Double & ub      )
{
    if ( !_defined )
        return;
    
    NOMAD::Double v0 = ( ref._defined ) ? ref : 0.0;
    
    if ( delta._defined && delta != 0.0 )
    {
        
        *this = v0 + ( (*this-v0) / delta).roundd() * delta;
        
        if ( ub._defined && *this > ub )
            *this = ub;
        
        if ( lb._defined && *this < lb )
            *this = lb;
    }
}
