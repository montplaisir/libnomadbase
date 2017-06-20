/**
 \file   Vector.hpp
 \brief  Vector
 \author Viviane Rochon Montplaisir
 \date   April 2017
 \see    Vector.cpp
 */

#ifndef __NOMAD400_VECTOR__
#define __NOMAD400_VECTOR__

#include "Math/Double.hpp"
#include "Math/Point.hpp"

#include "nomad_nsbegin.hpp"

    /// Class for the representation of a vector.
    /**
     A vector is defined by 2 points: initial point and end point.
     Alternatively, a vector is defined by 1 direction, in which case
     we consider the initial point to be the origin.
    */
    class Vector {
    private:
        /*---------*/
        /* Members */
        /*---------*/

        NOMAD::Point _initialPoint;    // Start of the vector
        NOMAD::Point _endPoint;        // End of the vector
        // VRM: 1- Maybe change this (initialPoint, endPoint) for initialPoint + direction.
        // It could be more useful.
        // 2- Dimension, Norm might also be useful to keep at this level.
        // 3- We don't verify that initialPoint and endPoint dimensions are identical, but we could.

    public:
        /*-------------*/
        /* Constructor */
        /*-------------*/
        // Constructor for vector defined by 2 points
        /**
         \param initialPoint Start of the vector -- \b IN
         \param endPoint End of the vector -- \b IN
         */
        explicit Vector ( const NOMAD::Point& initialPoint, const NOMAD::Point& endPoint );

        // Constructor for vector defined by 1 direction
        /**
         \param endPoint End of the vector -- \b IN
         */
        explicit Vector ( const NOMAD::Point& endPoint );

        /// Copy constructor.
        /**
         \param p The copied object -- \b IN.
         */
        Vector ( const Vector & v );

        /// Affectation operator.
        /**
         \param p The right-hand side object -- \b IN.
         \return \c *this as the result of the affectation.
         */
        const Vector & operator = ( const Vector & v );

        /// Destructor.
        ~Vector ( void );

        /*---------*/
        /* Get/Set */
        /*---------*/
        /// Access to the first point
        /**
         \return Initial point of the vector
         */
        NOMAD::Point get_initialPoint () const { return _initialPoint; }

        /// Access to the second point
        /**
         \return End point of the vector
         */
        NOMAD::Point get_endPoint () const { return _endPoint; }

        /*---------------*/
        /* Class methods */
        /*---------------*/
        /// Euclidian norm of the vector
        /**
         \return Norm (length) of the vector
         */
        NOMAD::Double norm () const;


        // VRM Other useful methods could be implemented: 
        // Equality, inequality; Normalization;
        // Addition/Substraction, Scalar multiplication, Dot product, Cross product, etc.

    };

#include "nomad_nsend.hpp"
#endif
