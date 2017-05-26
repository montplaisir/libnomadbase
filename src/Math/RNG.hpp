/**
 \file   RNG.hpp
 \brief  Custom class for random number generator
 \author Christophe Tribes and Sebastien Le Digabel 
 \date   2011-09-28
 \see    RNG.cpp
 */

#ifndef __NOMAD400_RNG__
#define __NOMAD400_RNG__

#include "Util/defines.hpp"
#include "Util/Exception.hpp"

using namespace std;

#include "nomad_nsbegin.hpp"

    
    /// Class for random number generator
	/**
     This class is used to set a seed for the random number generator and
     get a random integer or a random double between two values.
	 */
	class RNG {
		
	public:
        
        
 		/// Get current seed
		/*
		 /return An integer in [0,UINT32_MAX].
		 */
        static int get_seed ( void )
        {
            return static_cast<int>(_s);
        }
        
		/// Set seed
		/*
		 /param s The seed -- \b IN.
		 */
		static void set_seed(int s);
    
		
		/// Get a random integer as uint32
		/** This function serves to obtain a random number \c
		 /return An integer in the interval [0,UINT32_MAX].
		 */
		static uint32_t rand();
        
		
		/// Get a random number having a normal distribution as double
		/*
         /param a Lower bound  -- \b IN.
         /param b Upper bound  -- \b IN.
         /return A double in the interval [a,b].
		 */
		static double rand(double a, double b)
        {
            return a+((b-a)*NOMAD::RNG::rand())/UINT32_MAX;
        }
		
		/// Get a random number approaching a normal distribution (N(0,Var)) as double
		//  A series of Nsample random numbers Xi in the interval [-sqrt(3*Var);+sqrt(3*Var)] is used -> E[Xi]=0, Var(Xi)=var
		// see http://en.wikipedia.org/wiki/Central_limit_theorem
		/*
         /param Nsample	Number of samples for averaging				-- \b IN.
         /param Var		Variance of the target normal distribution	-- \b IN.
         /return A double in the interval [-sqrt(3*Var);+sqrt(3*Var)].
		 */
		static double normal_rand_mean_0( double Var=1 , int Nsample=12 ) ;
        
        
        /// Get a random number approaching a normal distribution ( N(Mean,Var) ) as double
		/*
         /param Mean	Mean of the target normal distribution		-- \b IN.
         /param Var		Variance of the target normal distribution	-- \b IN.
         /return A random number.
		 */
        static double normal_rand( double Mean=0 , double Var=1 ) ;
        
        /// Reset seed to its default value
        static void reset_private_seed_to_default ( void )
        {
            _x=x_def;
            _y=y_def;
            _z=z_def;
        }

        
        
	private:
        
        static uint32_t x_def,y_def,z_def,_x,_y,_z;  ///< Default parameter value for the random number generator (_s used as the seed).
        
        static int _s;
        

	};
#include "nomad_nsend.hpp"


#endif
