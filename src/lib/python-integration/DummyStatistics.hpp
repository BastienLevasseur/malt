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

        DomainStatistics& getDomainStatistics(const PythonAllocatorDomain& domain);

    public: 

        DummyStatistics();

        void mallocCountUp(const PythonAllocatorDomain& mallocDomain);
        void freeCountUp(const PythonAllocatorDomain& freeDomain);
        void callocCountUp(const PythonAllocatorDomain& callocDomain);
        void reallocCountUp(const PythonAllocatorDomain& reallocDomain);

        void locationCountUp(const PythonAllocatorDomain& locationDomain);
        void callStackCountUp(const PythonAllocatorDomain& callStackDomain);

        void emptyCallStackCountUp(const PythonAllocatorDomain& emptyCallStackDomain);
        void ptrIncoherenceCountUp(const PythonAllocatorDomain& ptrIncoherenceDomain);
        
        void mallocSumUp(const PythonAllocatorDomain& mallocDomain, size_t mallocSize);
        void callocSumUp(const PythonAllocatorDomain& callocDomain, size_t callocSize);

        size_t getMallocCount(const PythonAllocatorDomain& mallocDomain);
        size_t getFreeCount(const PythonAllocatorDomain& freeDomain);
        size_t getCallocCount(const PythonAllocatorDomain& callocDomain);
        size_t getReallocCount(const PythonAllocatorDomain& reallocDomain);

        size_t getMallocSum(const PythonAllocatorDomain& mallocDomain);
        size_t getCallocSum(const PythonAllocatorDomain& callocDomain);

        friend std::ostream& operator << (std::ostream &out, const DummyStatistics& globalStats);
        friend std::ostream& operator << (std::ostream &out, const DomainStatistics& domainStats);
};

}
#endif //DummyStatistics_hpp