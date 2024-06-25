#include "PythonHandler.hpp"
#include "PythonBacktraceStack.hpp"
#include "PythonLocation.hpp"

//FIXME: Remove it at some point
#define MALT_PYTHON_UNUSED(var) (void)(var)

namespace MALT {

PythonHandler::PythonHandler(DummyStatistics* dummyStats, PythonLocationTranslater* locationTranslater){
	this->dummyStats = dummyStats;
	this->locationTranslater = locationTranslater;
}


PythonHandler::~PythonHandler(){
	;
}

/**
 * Handles a Python malloc, fetch the backtrace stack and print it, updates statistics
 * FIXME: Behavior will change at some point to use MALT internals 
 */
void PythonHandler::onMalloc(const PythonAllocatorDomainType& pyMallocDomain, size_t size){
	assert(size != 0);
	
	this->dummyStats->mallocCountUp(pyMallocDomain);
	this->dummyStats->mallocSumUp(pyMallocDomain, size);

	std::vector<PythonLocation> allocationBacktraceStackVector = getPythonBacktraceStack();

	locationTranslater->insertLocations(pyMallocDomain, allocationBacktraceStackVector);
}


/**
 * Handles a Python free, fetch the backtrace stack and print it, updates statistics
 * FIXME: Behavior will change at some point to use MALT internals 
 */
void PythonHandler::onFree(const PythonAllocatorDomainType& pyMallocDomain, void* freePtr){
	MALT_PYTHON_UNUSED(freePtr);
	this->dummyStats->freeCountUp(pyMallocDomain);
	
	std::vector<PythonLocation> freeBacktraceStackVector = getPythonBacktraceStack();
	
	for (auto& backtraceStack : freeBacktraceStackVector){
		std::cout << backtraceStack << std::endl;
	}
}


/**
 * Handles a Python calloc, fetch the backtrace stack and print it, updates statistics
 * FIXME: Behavior will change at some point to use MALT internals 
 */
void PythonHandler::onCalloc(const PythonAllocatorDomainType& pyMallocDomain, size_t nbElements, size_t elementSize){
	assert(nbElements != 0);
	assert(elementSize != 0);
	this->dummyStats->callocCountUp(pyMallocDomain);
	this->dummyStats->callocSumUp(pyMallocDomain, nbElements*elementSize);

	std::vector<PythonLocation> callocBacktraceStackVector = getPythonBacktraceStack();

	for (auto& backtraceStack : callocBacktraceStackVector){
		std::cout << backtraceStack << std::endl;
	}
}


/**
 * Handles a Python realloc, fetch the backtrace stack and print it, updates statistics
 * FIXME: Behavior will change at some point to use MALT internals 
 */
void PythonHandler::onRealloc(const PythonAllocatorDomainType& pyMallocDomain, void* reallocPtr, size_t newSize){
	MALT_PYTHON_UNUSED(reallocPtr);
	MALT_PYTHON_UNUSED(newSize);
	assert(newSize != 0);

	this->dummyStats->reallocCountUp(pyMallocDomain);

	std::vector<PythonLocation> reallocBacktraceStackVector = getPythonBacktraceStack();

	for (auto& backtraceStack : reallocBacktraceStackVector){
		std::cout << backtraceStack << std::endl;
	}
}

}