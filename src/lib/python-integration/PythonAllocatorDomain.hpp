#ifndef PythonAllocatorDomain_hpp
#define PythonAllocatorDomain_hpp

#include "Python.h"

#define PYMALLOC_DOMAIN_COUNT 3

namespace MALT{

    typedef PyMemAllocatorDomain PythonAllocatorDomain;

    static const char* cstPyMallocDomains[PYMALLOC_DOMAIN_COUNT] = {
        "raw",
        "mem",
        "obj"
    };
}

#endif //PythonAllocatorDomain_hpp