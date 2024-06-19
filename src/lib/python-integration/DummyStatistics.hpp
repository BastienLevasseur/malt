#ifndef DummyStatistics_hpp
#define DummyStatistics_hpp

#include <map>
#include <sstream>
#include <vector>
#include "DummyAllocationMap.hpp"
#include "PythonAllocatorDomainType.hpp"

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

        DomainStatistics& getDomainStatistics(const PythonAllocatorDomainType& domain);

    public: 

        DummyStatistics();

        void mallocCountUp(const PythonAllocatorDomainType& mallocDomain);
        void freeCountUp(const PythonAllocatorDomainType& freeDomain);
        void callocCountUp(const PythonAllocatorDomainType& callocDomain);
        void reallocCountUp(const PythonAllocatorDomainType& reallocDomain);

        void locationCountUp(const PythonAllocatorDomainType& locationDomain);
        void callStackCountUp(const PythonAllocatorDomainType& callStackDomain);

        void emptyCallStackCountUp(const PythonAllocatorDomainType& emptyCallStackDomain);
        void ptrIncoherenceCountUp(const PythonAllocatorDomainType& ptrIncoherenceDomain);
        
        void mallocSumUp(const PythonAllocatorDomainType& mallocDomain, size_t mallocSize);
        void callocSumUp(const PythonAllocatorDomainType& callocDomain, size_t callocSize);

        size_t getMallocCount(const PythonAllocatorDomainType& mallocDomain);
        size_t getFreeCount(const PythonAllocatorDomainType& freeDomain);
        size_t getCallocCount(const PythonAllocatorDomainType& callocDomain);
        size_t getReallocCount(const PythonAllocatorDomainType& reallocDomain);

        size_t getMallocSum(const PythonAllocatorDomainType& mallocDomain);
        size_t getCallocSum(const PythonAllocatorDomainType& callocDomain);

        friend std::ostream& operator << (std::ostream &out, const DummyStatistics& globalStats);
        friend std::ostream& operator << (std::ostream &out, const DomainStatistics& domainStats);
};

}
#endif //DummyStatistics_hpp