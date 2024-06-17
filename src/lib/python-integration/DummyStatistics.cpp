#include <iostream>
#include "DummyStatistics.hpp"

namespace MALT{

DummyStatistics::DummyStatistics(){
    this->rawDomainType = DomainStatistics();
    this->memDomainType = DomainStatistics();
    this->objDomainType = DomainStatistics();
}


DummyStatistics::DomainStatistics& DummyStatistics::getDomainStatistics(const PythonAllocatorDomain& domain){
    switch(domain){
        case PYMEM_DOMAIN_RAW:
            return this->rawDomainType;
        case PYMEM_DOMAIN_MEM:
            return this->memDomainType;
        case PYMEM_DOMAIN_OBJ:
            return this->objDomainType;
        default:
            std::cerr << "Unknown domain : \"" << domain << "\"" << std::endl;
            exit(1);
    }
}


void DummyStatistics::mallocCountUp(const PythonAllocatorDomain& mallocDomain){
    this->getDomainStatistics(mallocDomain).nbMalloc++;
}

void DummyStatistics::freeCountUp(const PythonAllocatorDomain& freeDomain){
    this->getDomainStatistics(freeDomain).nbFree++;
}

void DummyStatistics::callocCountUp(const PythonAllocatorDomain& callocDomain){
    this->getDomainStatistics(callocDomain).nbCalloc++;
}

void DummyStatistics::reallocCountUp(const PythonAllocatorDomain& reallocDomain){
    this->getDomainStatistics(reallocDomain).nbRealloc++;
}

void DummyStatistics::locationCountUp(const PythonAllocatorDomain& locationDomain){
    this->getDomainStatistics(locationDomain).nbLocation++;
}

void DummyStatistics::callStackCountUp(const PythonAllocatorDomain &callStackDomain){
    this->getDomainStatistics(callStackDomain).nbCallStack++;
}

void DummyStatistics::emptyCallStackCountUp(const PythonAllocatorDomain &emptyCallStackDomain){
    this->getDomainStatistics(emptyCallStackDomain).nbEmptyCallStack++;
}

void DummyStatistics::ptrIncoherenceCountUp(const PythonAllocatorDomain &ptrIncoherenceDomain){
    this->getDomainStatistics(ptrIncoherenceDomain).nbPtrIncoherence++;
}

void DummyStatistics::mallocSumUp(const PythonAllocatorDomain& mallocDomain, size_t mallocSize){
    this->getDomainStatistics(mallocDomain).sumAlloc += mallocSize;
    this->getDomainStatistics(mallocDomain).allocationMap.insertAlloc(mallocSize);
}

void DummyStatistics::callocSumUp(const PythonAllocatorDomain& callocDomain, size_t callocSize){
    this->getDomainStatistics(callocDomain).sumCalloc += callocSize;
    this->getDomainStatistics(callocDomain).allocationMap.insertAlloc(callocSize);
}

size_t DummyStatistics::getMallocCount(const PythonAllocatorDomain& mallocDomain){
    return this->getDomainStatistics(mallocDomain).nbMalloc;
}

size_t DummyStatistics::getFreeCount(const PythonAllocatorDomain& freeDomain){
    return this->getDomainStatistics(freeDomain).nbFree;
}

size_t DummyStatistics::getCallocCount(const PythonAllocatorDomain& callocDomain){
    return this->getDomainStatistics(callocDomain).nbCalloc;
}

size_t DummyStatistics::getReallocCount(const PythonAllocatorDomain& reallocDomain){
    return this->getDomainStatistics(reallocDomain).nbRealloc;
}

size_t DummyStatistics::getMallocSum(const PythonAllocatorDomain& mallocDomain){
    return this->getDomainStatistics(mallocDomain).sumAlloc;
}

size_t DummyStatistics::getCallocSum(const PythonAllocatorDomain& callocDomain){
    return this->getDomainStatistics(callocDomain).sumCalloc;
}


std::ostream& operator << (std::ostream &out, const DummyStatistics& globalStats){
    std::stringstream ans;

    const DummyStatistics::DomainStatistics listDomain[PYMALLOC_DOMAIN_COUNT] = {globalStats.rawDomainType, globalStats.memDomainType, globalStats.objDomainType};

    for (size_t i = 0; i < PYMALLOC_DOMAIN_COUNT ; i++){
        
        ans << "========== For domain : " << cstPyMallocDomains[i] << " ==========\n";
        ans << listDomain[i].nbMalloc << " of mallocs\n";
        ans << listDomain[i].nbFree << " of frees\n";
        ans << listDomain[i].nbCalloc << " of callocs\n";
        ans << listDomain[i].nbRealloc << " of reallocs\n\n";

        ans << listDomain[i].sumAlloc << " alloced\n";
        ans << listDomain[i].sumCalloc << " calloced\n\n";
        
        ans << listDomain[i].nbLocation << " of locations\n";
        ans << listDomain[i].nbBacktrace << " of backtraces\n\n";
        
        ans << listDomain[i].nbEmptyCallStack << " of empty callstacks\n";
        ans << listDomain[i].nbPtrIncoherence  << " of incoherences on PyCode pointers\n";
        ans << "======================================\n" << std::endl;
        
        ans << listDomain[i].allocationMap.getTop(cstPyMallocDomains[i]);
    }

    out << ans.str();
    return out;
}


DummyStatistics::DomainStatistics::DomainStatistics(){
    this->allocationMap = DummyAllocationMap();

    this->nbMalloc = 0;
    this->nbFree = 0;
    this->nbCalloc = 0;
    this->nbRealloc = 0;

    this->sumAlloc = 0;
    this->sumCalloc = 0;

    this->nbLocation = 0;
    this->nbCallStack = 0;
    this->nbBacktrace = 0;

    this->nbPtrIncoherence = 0;
    this->nbEmptyCallStack = 0;
}


DummyStatistics::DomainStatistics::~DomainStatistics(){
    ;
}


std::ostream& operator << (std::ostream &out, const DummyStatistics::DomainStatistics& domainStats){
    std::stringstream ans;

    ans << domainStats.nbMalloc << " allocations\n";
    ans << domainStats.nbFree << " free\n\n";

    ans << domainStats.sumAlloc << " total alloced\n\n";

    ans << domainStats.nbLocation << " locations\n";
    ans << domainStats.nbBacktrace << " backtraces\n\n";
    
    ans << domainStats.nbEmptyCallStack << " empty callstacks\n";
    ans << domainStats.nbPtrIncoherence  << " incoherences on PyCode pointers" << std::endl;

    out << ans.str();
    return out;
}

}