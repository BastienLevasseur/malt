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
} MaltPythonAllocatorWrapper_t;


/** 
 * The entry point into the MALT Python allocator.
 * Makes the bridge between the orignal Python allocator and the MALT Python allocator.
 */
class MaltPythonAllocator {

    //FIXME: "Wrapper" has two meanings... :
    // MaltPythonAllocatorWrapper_t & PythonAllocatorWrapper_t are wrappers in the sense they wrap the three domains
    // PythonDomainAllocatorWrapper is a wrapper in the sense it wraps the Python allocator
    //FIXME: Rename one of those, probably the PythonDomainAllocatorWrapper

    public:
        MaltPythonAllocator(PythonHandler* pythonHandler);
        ~MaltPythonAllocator();

        void enable();
        void disable();

        bool isEnabled();

    private:
        /* The original Python allocator */
        PythonAllocatorWrapper_t* originalAllocator;

        /* The MALT custom Python allocator */
        PythonAllocatorWrapper_t* customAllocator;
    
        PythonHandler* pythonHandler;

        bool enabledFlag;

        PythonGuard* pythonGuard;

        MaltPythonAllocatorWrapper_t* maltAllocatorWrapper;

    private:
        MaltPythonAllocatorWrapper_t* initialiseMaltPythonAllocatorWrapper();
        void destroyMaltPythonAllocatorWrapper(MaltPythonAllocatorWrapper_t* maltPythonAllocator);

        PythonAllocatorWrapper_t* initialisePythonAllocator();
        void destroyPythonAllocator(PythonAllocatorWrapper_t* pythonAllocator);

        void getPythonAllocatorFunctions(PythonAllocatorWrapper_t* pythonAllocator);
        void setPythonAllocator(PythonAllocatorWrapper_t* pythonAllocator);
};


}

#endif //MaltPythonAllocator_hpp

