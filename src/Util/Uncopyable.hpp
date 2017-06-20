/**
  \file   Uncopyable.hpp
  \brief  Base class for uncopyable classes (headers)
  \author Sebastien Le Digabel
  \date   2010-04-02
*/
#ifndef __NOMAD400_UNCOPYABLE__
#define __NOMAD400_UNCOPYABLE__

#include "nomad_nsbegin.hpp"

  /// Uncopyable class.
  /**
     Base class for uncopyable classes
     (see Scott Meyer's Effective C++, 3rd ed., item #6).
  */
  class Uncopyable {

  protected:

    /// Constructor.
    explicit Uncopyable  ( void ) {}

    /// Destructor.
    // VRM Although Uncopyable is a base class, it is not polymorphic:
    // its derived class types are not manipulated through Uncopyable's
    // interface, they are manipulated directly.
    // For this reason, we do not need to make the destructor virtual.
    // See Effective C++ Item 7.
    ~Uncopyable ( void ) {}

  private:

    /// Undefined copy constructor.
    Uncopyable ( const Uncopyable & );

    /// Undefined affectation operator.
    Uncopyable & operator = ( const Uncopyable & );
  };
#include "nomad_nsend.hpp"

#endif
                                             
