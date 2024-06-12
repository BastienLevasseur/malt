#ifndef DummyStatistics_hpp
#define DummyStatistics_hpp

#include <map>
#include <sstream>
#include <vector>
#include "DummyAllocationMap.hpp"
#include "PythonAllocatorDomain.hpp"

namespace MALT{

/** A dummy Statistics class, will be replaced by MALT implementation */
class DummyStatistics {
    private:
        class DomainStatistics{
            public:

                DomainStatistics(void);
                ~DomainStatistics(void);

                DummyAllocationMap allocationMap;

                size_t nbMalloc;
                size_t nbFree;
                size_t nbCalloc;
                size_t nbRealloc;

                size_t sumAlloc;
                size_t sumCalloc;

                size_t nbLocation;
                size_t nbCallStack;
                size_t nbBacktrace;

                size_t nbPtrIncoherence;
                size_t nbEmptyCallStack;
        };

    private:
        DomainStatistics rawDomainType;
        DomainStatistics memDomainType;
        DomainStatistics objDomainType;

        DomainStatistics& getDomainStatistics(PythonAllocatorDomain& domain);

    public: 

        DummyStatistics();

        void mallocCountUp(PythonAllocatorDomain& mallocDomain);
        void freeCountUp(PythonAllocatorDomain& freeDomain);
        void callocCountUp(PythonAllocatorDomain& callocDomain);
        void reallocCountUp(PythonAllocatorDomain& reallocDomain);

        void locationCountUp(PythonAllocatorDomain& locationDomain);
        void callStackCountUp(PythonAllocatorDomain& callStackDomain);

        void emptyCallStackCountUp(PythonAllocatorDomain& emptyCallStackDomain);
        void ptrIncoherenceCountUp(PythonAllocatorDomain& ptrIncoherenceDomain);
        
        void mallocSumUp(PythonAllocatorDomain& mallocDomain, size_t mallocSize);
        void callocSumUp(PythonAllocatorDomain& callocDomain, size_t callocSize);

        friend std::ostream& operator << (std::ostream &out, const DummyStatistics& globalStats);
        friend std::ostream& operator << (std::ostream &out, const DomainStatistics& domainStats);
};

}
#endif //DummyStatistics_hpp