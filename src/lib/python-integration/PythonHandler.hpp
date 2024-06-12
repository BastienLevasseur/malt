#ifndef PythonHandler_hpp
#define PythonHandler_hpp

#include "DummyStatistics.hpp"
#include "PythonAllocatorDomain.hpp"

namespace MALT {

    /**
     * Handler for Python malloc/free/calloc/realloc. 
     * FIXME: Currently only log the allocation and print the stack trace, will be replaced by MALT own logic
     */
    class PythonHandler {
            
        public:
            PythonHandler();
            ~PythonHandler();

            void maltLogPythonAlloc(PythonAllocatorDomain pyMallocDomain, size_t size);

            void maltLogPythonFree(PythonAllocatorDomain pyMallocDomain, void* freePtr);

            void maltLogPythonCalloc(PythonAllocatorDomain pyMallocDomain, size_t nbElements, size_t elementSize);

            void maltLogPythonRealloc(PythonAllocatorDomain pyMallocDomain, void* reallocPtr, size_t newSize);

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