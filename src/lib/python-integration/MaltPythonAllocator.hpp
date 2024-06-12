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

void initialiseMaltPythonAllocator(PythonHandler* pythonHandler);
void destroyMaltPythonAllocator(void);

void enableMaltPythonAllocator(void);
void disableMaltPythonAllocator(void);

void printRecursiveFault(void);
}
#endif //MaltPythonAllocator_hpp

