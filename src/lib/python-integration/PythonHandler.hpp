#ifndef PythonHandler_hpp
#define PythonHandler_hpp

#include "DummyStatistics.hpp"
#include "PythonAllocatorDomainType.hpp"
#include "PythonLocationTranslater.hpp"

namespace MALT {

    /**
     * Handler for Python malloc/free/calloc/realloc. 
     * FIXME: Currently only log the allocation and print the stack trace, will be replaced by MALT own logic
     */
    class PythonHandler {
            
        public:
            PythonHandler(DummyStatistics* dummsyStats, PythonLocationTranslater* locationTranslater);
            ~PythonHandler();

            virtual void onMalloc(const PythonAllocatorDomainType& pyMallocDomain, size_t size);

            virtual void onFree(const PythonAllocatorDomainType& pyMallocDomain, void* freePtr);

            virtual void onCalloc(const PythonAllocatorDomainType& pyMallocDomain, size_t nbElements, size_t elementSize);

            virtual void onRealloc(const PythonAllocatorDomainType& pyMallocDomain, void* reallocPtr, size_t newSize);

            void getPythonBacktraceStack(void);

        private:
            PythonHandler(const PythonHandler& ref) = delete;
            /* FIXME: Will be replaced by MALT own concepts
            CallStackMap* callStackMap;
            GlobalStatistics* globalStats;
            LocationTranslater* locationTranslater;
            */

            //FIXME: Placeholder, will be replaced by MALT own statistics
            DummyStatistics* dummyStats;
            PythonLocationTranslater* locationTranslater;
    };
}

#endif //PythonHandler_hpp