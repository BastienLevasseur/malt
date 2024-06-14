#ifndef MaltPythonAllocator_hpp
#define MaltPythonAllocator_hpp

#include "PythonHandler.hpp"
#include "Python.h"

namespace MALT {

//Rename the Python Allocator type into a better name
typedef PyMemAllocatorEx PythonAllocatorPerDomain;

/** The MALT custom Python allocator that wraps the original Python allocator */
typedef struct MaltPythonAllocator{
    /* The original Python allocator, separated into the three domains */
    PythonAllocatorPerDomain* originalAllocatorRaw;
    PythonAllocatorPerDomain* originalAllocatorMem;
    PythonAllocatorPerDomain* originalAllocatorObj;

    /* The MALT custom Python allocator, also separated into three domains */
    PythonAllocatorPerDomain* maltAllocatorRaw;
    PythonAllocatorPerDomain* maltAllocatorMem;
    PythonAllocatorPerDomain* maltAllocatorObj;

    bool recursiveGuard;
    bool enabledFlag;

    PythonHandler* maltPythonHandler;

    size_t recursiveFault;
} MaltPythonAllocator_t;

MaltPythonAllocator_t* initialiseMaltPythonAllocator(PythonHandler* pythonHandler);
void destroyMaltPythonAllocator(MaltPythonAllocator_t* maltAllocator);

void enableMaltPythonAllocator(MaltPythonAllocator_t* maltAllocator);
void disableMaltPythonAllocator(MaltPythonAllocator_t* maltAllocator);

void printRecursiveFault(MaltPythonAllocator_t* maltAllocator);
}

#endif //MaltPythonAllocator_hpp

