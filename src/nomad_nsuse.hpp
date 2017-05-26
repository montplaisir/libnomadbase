
#ifndef __NOMAD400_NAMESPACE_NOMAD__
#define __NOMAD400_NAMESPACE_NOMAD__

#include "nomad_version.hpp"

#ifndef NOMAD_NAMESPACE_USING
    #define NOMAD_NAMESPACE_USING 1
#endif

#if defined(NOMAD_NAMESPACE) && (NOMAD_NAMESPACE_USING == 1)
    using namespace NOMAD;
#endif

#endif
