#ifndef PythonHandler_hpp
#define PythonHandler_hpp

#include "DummyStatistics.hpp"
#include "PythonAllocatorDomainType.hpp"

namespace MALT {

    /**
     * Handler for Python malloc/free/calloc/realloc. 
     * FIXME: Currently only log the allocation and print the stack trace, will be replaced by MALT own logic
     */
    class PythonHandler {
            
        public:
            PythonHandler(DummyStatistics* dummsyStats);
            ~PythonHandler();

            void maltLogPythonAlloc(const PythonAllocatorDomainType& pyMallocDomain, size_t size);

            void maltLogPythonFree(const PythonAllocatorDomainType& pyMallocDomain, void* freePtr);

            void maltLogPythonCalloc(const PythonAllocatorDomainType& pyMallocDomain, size_t nbElements, size_t elementSize);

            void maltLogPythonRealloc(const PythonAllocatorDomainType& pyMallocDomain, void* reallocPtr, size_t newSize);

        private:

            /* FIXME: Will be replaced by MALT own concepts
            CallStackMap* callStackMap;
            GlobalStatistics* globalStats;
            LocationTranslater* locationTranslater;
            */

            //FIXME: Placeholder, will be replaced by MALT own statistics
            DummyStatistics* dummyStats;
    };
}

#endif //PythonHandler_hpp