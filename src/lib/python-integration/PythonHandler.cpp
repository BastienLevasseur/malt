#include "PythonHandler.hpp"
#include "PythonBacktraceStack.hpp"
#include "DummyLocation.hpp"

//FIXME: Remove it at some point
#define MALT_PYTHON_UNUSED(var) (void)(var)

namespace MALT {

PythonHandler::PythonHandler(){
	this->dummyStats = new DummyStatistics();
}


PythonHandler::~PythonHandler(){
	delete this->dummyStats;
}

/**
 * Handles a Python malloc, fetch the backtrace stack and print it, updates statistics
 * FIXME: Behavior will change at some point to use MALT internals 
 */
void PythonHandler::maltLogPythonAlloc(PythonAllocatorDomain pyMallocDomain, size_t size){
	this->dummyStats->mallocCountUp(pyMallocDomain);
	this->dummyStats->mallocSumUp(pyMallocDomain, size);

	std::vector<DummyLocation> allocationBacktraceStackVector = getPythonBacktraceStack();
	
	for (auto& backtraceStack : allocationBacktraceStackVector){
		std::cout << backtraceStack << std::endl;
	}
}


/**
 * Handles a Python free, fetch the backtrace stack and print it, updates statistics
 * FIXME: Behavior will change at some point to use MALT internals 
 */
void PythonHandler::maltLogPythonFree(PythonAllocatorDomain pyMallocDomain, void* freePtr){
	MALT_PYTHON_UNUSED(freePtr);
	this->dummyStats->freeCountUp(pyMallocDomain);
	
	std::vector<DummyLocation> freeBacktraceStackVector = getPythonBacktraceStack();
	
	for (auto& backtraceStack : freeBacktraceStackVector){
		std::cout << backtraceStack << std::endl;
	}
}


/**
 * Handles a Python calloc, fetch the backtrace stack and print it, updates statistics
 * FIXME: Behavior will change at some point to use MALT internals 
 */
void PythonHandler::maltLogPythonCalloc(PythonAllocatorDomain pyMallocDomain, size_t nbElements, size_t elementSize){
	
	this->dummyStats->callocCountUp(pyMallocDomain);
	this->dummyStats->callocSumUp(pyMallocDomain, nbElements*elementSize);

	std::vector<DummyLocation> callocBacktraceStackVector = getPythonBacktraceStack();

	for (auto& backtraceStack : callocBacktraceStackVector){
		std::cout << backtraceStack << std::endl;
	}
}


/**
 * Handles a Python realloc, fetch the backtrace stack and print it, updates statistics
 * FIXME: Behavior will change at some point to use MALT internals 
 */
void PythonHandler::maltLogPythonRealloc(PythonAllocatorDomain pyMallocDomain, void* reallocPtr, size_t newSize){
	MALT_PYTHON_UNUSED(reallocPtr);
	MALT_PYTHON_UNUSED(newSize);

	this->dummyStats->reallocCountUp(pyMallocDomain);

	std::vector<DummyLocation> reallocBacktraceStackVector = getPythonBacktraceStack();

	for (auto& backtraceStack : reallocBacktraceStackVector){
		std::cout << backtraceStack << std::endl;
	}
}

}