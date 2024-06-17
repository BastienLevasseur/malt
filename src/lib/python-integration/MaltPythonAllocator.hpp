#ifndef MaltPythonAllocator_hpp
#define MaltPythonAllocator_hpp

#include "PythonHandler.hpp"
#include "Python.h"

namespace MALT {

//Rename the Python Allocator type into a better name
typedef PyMemAllocatorEx PythonAllocatorPerDomain;

//Wrapping the three domains of the Python allocator into one struct
typedef struct PythonAllocator{
    PythonAllocatorPerDomain* allocatorRaw;
    PythonAllocatorPerDomain* allocatorMem;
    PythonAllocatorPerDomain* allocatorObj;
} PythonAllocator_t;


/** The MALT custom Python allocator that wraps the original Python allocator */
typedef struct MaltPythonAllocator{
    /* The original Python allocator */
    PythonAllocator_t* originalAllocator;
    
    /* The MALT custom Python allocator */
    PythonAllocator_t* customAllocator;

    PythonHandler* maltPythonHandler;

    bool recursiveGuard;
    bool enabledFlag;
} MaltPythonAllocator_t;

void getPythonAllocatorFunctions(PythonAllocator_t* pythonAllocator);

void setPythonAllocatorFunctions(PythonAllocator_t* pythonAllocator);

PythonAllocator_t* initialisePythonAllocator();
void destroyPythonAllocator(PythonAllocator_t* pythonAllocator);

void initialiseMaltPythonAllocator(PythonHandler* pythonHandler);
void destroyMaltPythonAllocator(MaltPythonAllocator_t* maltPythonAllocator);

void enableMaltPythonAllocator(MaltPythonAllocator_t* maltPythonAllocator);
void disableMaltPythonAllocator(MaltPythonAllocator_t* maltPythonAllocator);

MaltPythonAllocator_t* getGlobalMaltPythonAllocator();
}

#endif //MaltPythonAllocator_hpp

