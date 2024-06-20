#ifndef MaltPythonAllocator_hpp
#define MaltPythonAllocator_hpp

#include "PythonHandler.hpp"
#include "PythonDomainAllocatorWrapper.hpp"

#include "Python.h"

namespace MALT {

/** Wrapper for the three domains of the orignal Python allocator */
typedef struct PythonAllocatorWrapper{
    PythonAllocatorDomain* allocatorRaw;
    PythonAllocatorDomain* allocatorMem;
    PythonAllocatorDomain* allocatorObj;
} PythonAllocatorWrapper_t;


/** Wrapper for the three domains of the MALT Python allocator */
typedef struct MaltPythonAllocatorWrapper{
    PythonDomainAllocatorWrapper* allocatorRaw;
    PythonDomainAllocatorWrapper* allocatorMem;
    PythonDomainAllocatorWrapper* allocatorObj;
} CustomPythonAllocatorWrapper_t;


/** 
 * The entry point into the MALT Python allocator.
 * Hooks the MALT Python allocator into the orignal Python allocator.
 */
class PythonAllocatorHooking {

    public:
        PythonAllocatorHooking(PythonHandler* pythonHandler);
        ~PythonAllocatorHooking();

        void enable();
        void disable();

        bool isEnabled();

    private:
        /* Wrapper for the original Python allocator */
        PythonAllocatorWrapper_t* originalAllocator;

        /* Wrapper for the MALT Python allocator */
        PythonAllocatorWrapper_t* customAllocator;
    
        PythonHandler* pythonHandler;

        /* The MALT custom Python allocator */
        CustomPythonAllocatorWrapper_t* maltAllocatorWrapper;

        bool enabledFlag;

        PythonGuard* pythonGuard;


    private:
        CustomPythonAllocatorWrapper_t* initialiseMaltPythonAllocatorWrapper();
        void destroyMaltPythonAllocatorWrapper(CustomPythonAllocatorWrapper_t* maltPythonAllocator);

        PythonAllocatorWrapper_t* initialisePythonAllocator();
        void destroyPythonAllocator(PythonAllocatorWrapper_t* pythonAllocator);

        void getPythonAllocatorFunctions(PythonAllocatorWrapper_t* pythonAllocator);
        void setPythonAllocator(PythonAllocatorWrapper_t* pythonAllocator);
};


}

#endif //MaltPythonAllocator_hpp

