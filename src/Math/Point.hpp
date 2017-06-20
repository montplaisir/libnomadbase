/**
 \file   Point.hpp
 \brief  Point
 \author Viviane Rochon Montplaisir
 \date   March 2017
 \see    Point.cpp
 */

#ifndef __NOMAD400_POINT__
#define __NOMAD400_POINT__

#include <numeric>
#include "Math/Double.hpp"

#include "nomad_nsbegin.hpp"

    /// \c accumulate operator for \c size_of().
    struct memsize_of_op {
        /** This function returns \c i+size_of(d) and is designed as an
         \c accumulate operator.
         \param i The integer \c i -- \b IN.
         \param d The NOMAD::Double \c d -- \b IN.
         \return An integer equal to \c i+size_of(d).
         */
        int operator () ( int i , const NOMAD::Double & d )
        {
            return i + d.mem_sizeof();
        }
    };

    /// Class for the representation of a point.
    /**
     A point is defined by its size and its coordinates.
    */
    class Point {
    private:
        /*---------*/
        /* Members */
        /*---------*/

        int _n;                     // Dimension of the point
        NOMAD::Double* _coords;     // Coordinates of the point

    public:
        /*-------------*/
        /* Constructor */
        /*-------------*/
        /**
         \param n Dimension of the point -- \b IN --\b optional (default = 0).
         \param val Initial value for all coordinates
         -- \b IN -- \b optional (default = undefined real).
         */
        explicit Point ( const int n = 0 , const NOMAD::Double & val = NOMAD::Double() );

        /// Copy constructor.
        /**
         \param p The copied object -- \b IN.
         */
        Point ( const Point & p );

        /// Affectation operator.
        /**
         \param p The right-hand side object -- \b IN.
         \return \c *this as the result of the affectation.
         */
        const Point & operator = ( const Point & p );

        /// Destructor.
        ~Point ( void );

        /*---------*/
        /* Get/Set */
        /*---------*/
        /// Const operator \c [].
        /**
         \param i The index (0 for the first element) -- \b IN.
         \return The \c (i+1)th coordinate.
         */
        const NOMAD::Double & operator [] ( int i ) const;

        /// Non-const operator \c [].
        /**
         \param i The index (0 for the first element) -- \b IN.
         \return The \c (i+1)th coordinate.
         */
        NOMAD::Double & operator [] ( int i );

        /// Access to the dimension of the point.
        /**
         \return The dimension of the point.
         */
        int get_size ( void ) const { return _n; }

        /*------------*/
        /* Comparison */
        /*------------*/
        /// Comparison operator \c ==.
        /**
         \param p The right-hand side object -- \b IN.
         \return A boolean equal to \c true if  \c *this \c == \c p.
         */
        bool operator == ( const Point & p ) const;

        /// Comparison operator \c !=.
        /**
         \param p The right-hand side object -- \b IN.
         \return A boolean equal to \c true if  \c *this \c != \c p.
         */
        bool operator != ( const Point & p ) const { return !(*this == p); }

        /// Comparison operator \c <.
        /**
         \param p The right-hand side object -- \b IN.
         \return A boolean equal to \c true if  \c *this \c < \c p.
         */
        bool operator <  ( const Point & p ) const;

        /*---------*/
        /* Display */
        /*---------*/
        /// Display.
        /**
         \param sep A string that is used as a separator between the coordinates
         -- \b IN --\b optional (default = one space).
         \param w   An integer indicating a width for the display of
         each coordinate -- \b IN -- \b optional
         (default = -1, no limit).
         \param lim Max number of coordinates to display -- \b IN
         -- \b optional (default = -1, no limit).
         */
        void display ( std::ostream& out,
                                      const std::string    & sep = " " ,
                                      int                    w   = -1  ,
                                      int                    lim = -1    ) const;


        /*---------------*/
        /* Class methods */
        /*---------------*/
        /// Size of the point in memory.
        /**
         \return Size of the point in memory, in bytes.
         */
        int mem_sizeof ( void ) const
        {
            return std::accumulate ( _coords,
                                    _coords+_n,
                                    static_cast<int>(sizeof(_n)),
                                    memsize_of_op());

        }

    };

    std::ostream& operator<< (std::ostream& out, const NOMAD::Point& point);

#include "nomad_nsend.hpp"
#endif
