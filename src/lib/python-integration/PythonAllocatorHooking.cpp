#include "PythonAllocatorHooking.hpp"
#include "PythonGuard.hpp"

#include <common/Debug.hpp>

namespace MALT{

/**
 * Overlap for the Raw domain, malloc function.
 */
void* Malt_PyMem_RawMalloc(void* ctx, size_t size){;
	return ((PythonDomainAllocatorWrapper*) ctx)->onMalloc(ctx, size);
}
/**
	Overlap for the Raw domain, Free function.
 */
void Malt_PyMem_RawFree(void* ctx, void* ptr){
	return ((PythonDomainAllocatorWrapper*) ctx)->onFree(ctx, ptr);
}

// Overlap for the Raw domain, Calloc function.
void* Malt_PyMem_RawCalloc(void* ctx, size_t nelem, size_t elsize){
	return ((PythonDomainAllocatorWrapper*) ctx)->onCalloc(ctx, nelem, elsize);
}

// Overlap for the Raw domain, Realloc function.
void* Malt_PyMem_RawRealloc(void* ctx, void *ptr, size_t new_size){
	return ((PythonDomainAllocatorWrapper*) ctx)->onRealloc(ctx, ptr, new_size);
}


/** Overlap for the Mem domain, Malloc function. */
void* Malt_PyMem_Malloc(void* ctx, size_t size){
	return ((PythonDomainAllocatorWrapper*) ctx)->onMalloc(ctx, size);
}

/** Overlap for the Mem domain, Free function. */
void Malt_PyMem_Free(void* ctx, void* ptr){
	return ((PythonDomainAllocatorWrapper*) ctx)->onFree(ctx, ptr);
}

/** Overlap for the Mem domain, Calloc function. */
void* Malt_PyMem_Calloc(void* ctx, size_t nelem, size_t elsize){
	return ((PythonDomainAllocatorWrapper*) ctx)->onCalloc(ctx, nelem, elsize);
}

/** Overlap for the Mem domain, Realloc function. */ 
void* Malt_PyMem_Realloc(void* ctx, void *ptr, size_t new_size){
	return ((PythonDomainAllocatorWrapper*) ctx)->onRealloc(ctx, ptr, new_size);
}



/** Overlap for the Obj domain, Malloc function. */
void* Malt_PyObject_Malloc(void* ctx, size_t size){
	return ((PythonDomainAllocatorWrapper*) ctx)->onMalloc(ctx, size);
}

/** Overlap for the Obj domain, Free function. */
void Malt_PyObject_Free(void* ctx, void* ptr){
	return ((PythonDomainAllocatorWrapper*) ctx)->onFree(ctx, ptr);
}

/** Overlap for the Mem domain, Calloc function. */
void* Malt_PyObject_Calloc(void* ctx, size_t nelem, size_t elsize){
	return ((PythonDomainAllocatorWrapper*) ctx)->onCalloc(ctx, nelem, elsize);
}

/** Overlap for the Mem domain, Realloc function. */
void* Malt_PyObject_Realloc(void* ctx, void *ptr, size_t new_size){
	return ((PythonDomainAllocatorWrapper*) ctx)->onRealloc(ctx, ptr, new_size);
}



/** 
 * Constructor for the MALT Python allocator.
 * Creates a the MALT Python allocator, ready to be enabled into the Python Interpreter.
 * @param pythonHandler : A pointer to a Python Handler.
 */
PythonAllocatorHooking::PythonAllocatorHooking(PythonHandler* pythonHandler){
	this->pythonHandler = pythonHandler;

	this->pythonGuard = new PythonGuard();

	this->originalAllocator = initialisePythonAllocator();
	getPythonAllocatorFunctions(this->originalAllocator);

	this->customAllocator = initialisePythonAllocator();

	this->customAllocator->allocatorRaw->malloc = Malt_PyMem_RawMalloc;
	this->customAllocator->allocatorRaw->free = Malt_PyMem_RawFree;
	this->customAllocator->allocatorRaw->calloc = Malt_PyMem_RawCalloc;
	this->customAllocator->allocatorRaw->realloc = Malt_PyMem_RawRealloc;

	this->customAllocator->allocatorMem->malloc = Malt_PyMem_Malloc;
	this->customAllocator->allocatorMem->free = Malt_PyMem_Free;
	this->customAllocator->allocatorMem->calloc = Malt_PyMem_Calloc;
	this->customAllocator->allocatorMem->realloc = Malt_PyMem_Realloc;

	this->customAllocator->allocatorObj->malloc = Malt_PyObject_Malloc;
	this->customAllocator->allocatorObj->free = Malt_PyObject_Free;
	this->customAllocator->allocatorObj->calloc = Malt_PyObject_Calloc;
	this->customAllocator->allocatorObj->realloc = Malt_PyObject_Realloc;

	this->maltAllocatorWrapper = initialiseMaltPythonAllocatorWrapper();

	this->enabledFlag = false;
}

/**
 * Deletes the MALT Python allocator.
 */
PythonAllocatorHooking::~PythonAllocatorHooking(){
	if (this->enabledFlag != false){
		MALT_WARNING("MALT Python allocator was not disabled before deletion. Python will likely crash !");
	}

	destroyMaltPythonAllocatorWrapper(this->maltAllocatorWrapper);

	destroyPythonAllocator(this->customAllocator);

	//FIXME: Python must be stopped before destroying the allocator, otherwise Python will have no functions to alloc/free and crash
	//FIXME: Maybe add an assert(Py_IsInitialized()==false)
	destroyPythonAllocator(this->originalAllocator);

	delete this->pythonGuard;
}

/**
 * Enables the MALT Python allocator into the Python Interpreter.
 */
void PythonAllocatorHooking::enable(){
	assert(this->enabledFlag == false);
	this->enabledFlag = true;

	setPythonAllocator(this->customAllocator);
}

/**
 * Disables the MALT Python allocator from the Python Interpreter.
 * Replaced by the original Python allocator
 */
void PythonAllocatorHooking::disable(){
	assert(this->enabledFlag == true);
	this->enabledFlag = false;

	setPythonAllocator(this->originalAllocator);
}

/**
 * Verify if the MALT Python allocator is currently enabled.
 */
bool PythonAllocatorHooking::isEnabled(){
    return this->enabledFlag;
}

/**
 * Initializer for a MALT Python allocator wrapper, wraps three MALT Python allocators into one structure. One for each domain.
 */
CustomPythonAllocatorWrapper_t* PythonAllocatorHooking::initialiseMaltPythonAllocatorWrapper(){
	CustomPythonAllocatorWrapper_t* allocator = new CustomPythonAllocatorWrapper_t();
	
	allocator->allocatorRaw = new PythonDomainAllocatorWrapper(this->pythonHandler, PYMEM_DOMAIN_RAW, this->pythonGuard, this->originalAllocator->allocatorRaw);
	allocator->allocatorMem = new PythonDomainAllocatorWrapper(this->pythonHandler, PYMEM_DOMAIN_MEM, this->pythonGuard, this->originalAllocator->allocatorMem);
	allocator->allocatorObj = new PythonDomainAllocatorWrapper(this->pythonHandler, PYMEM_DOMAIN_OBJ, this->pythonGuard, this->originalAllocator->allocatorObj);

	return allocator;
}

/**
 * Destroys a MALT Python allocator wrapper.
 * @param maltPythonAllocatorWrapper : The wrapper to be destroyed.
 */
void PythonAllocatorHooking::destroyMaltPythonAllocatorWrapper(CustomPythonAllocatorWrapper_t* maltPythonAllocatorWrapper){
	delete maltPythonAllocatorWrapper->allocatorObj;
	delete maltPythonAllocatorWrapper->allocatorMem;
	delete maltPythonAllocatorWrapper->allocatorRaw;

	delete maltPythonAllocatorWrapper;
}

/**
 * Initialises a Python Allocator wrapper, wraps three Python allocators into one structure. One for each domain.
 */
PythonAllocatorWrapper_t* PythonAllocatorHooking::initialisePythonAllocator(){
	PythonAllocatorWrapper_t* pythonAllocator = new PythonAllocatorWrapper_t();
	pythonAllocator->allocatorRaw = new PythonAllocatorDomain();
	pythonAllocator->allocatorMem = new PythonAllocatorDomain();
	pythonAllocator->allocatorObj = new PythonAllocatorDomain();
	return pythonAllocator;
}

/**
 * Destroys a Python Allocator.
 * @param pythonAllocatorWrapper : The wrapper to be destroyed.
 */
void PythonAllocatorHooking::destroyPythonAllocator(PythonAllocatorWrapper_t* pythonAllocatorWrapper){
	delete pythonAllocatorWrapper->allocatorObj;
	delete pythonAllocatorWrapper->allocatorMem;
	delete pythonAllocatorWrapper->allocatorRaw;

	delete pythonAllocatorWrapper;
}

/**
 * Get the three Python allocators corresponding to the three domains.
 * @param pythonAllocatorWrapper : The wrapper to be filled.
 *  */
void PythonAllocatorHooking::getPythonAllocatorFunctions(PythonAllocatorWrapper_t* pythonAllocatorWrapper){
	PyMem_GetAllocator(PYMEM_DOMAIN_RAW, pythonAllocatorWrapper->allocatorRaw);
	PyMem_GetAllocator(PYMEM_DOMAIN_MEM, pythonAllocatorWrapper->allocatorMem);
	PyMem_GetAllocator(PYMEM_DOMAIN_OBJ, pythonAllocatorWrapper->allocatorObj);
}

/**
 *  Set the three Python allocators corresponding to the three domains.
 * @param pythonAllocatorWrapper : The wrapper to be set.
 *  */
void PythonAllocatorHooking::setPythonAllocator(PythonAllocatorWrapper_t* pythonAllocatorWrapper){
	assert(pythonAllocatorWrapper->allocatorRaw != nullptr);
	assert(pythonAllocatorWrapper->allocatorMem != nullptr);
	assert(pythonAllocatorWrapper->allocatorObj != nullptr);

	pythonAllocatorWrapper->allocatorRaw->ctx = this->maltAllocatorWrapper->allocatorRaw;
	pythonAllocatorWrapper->allocatorMem->ctx = this->maltAllocatorWrapper->allocatorMem;
	pythonAllocatorWrapper->allocatorObj->ctx = this->maltAllocatorWrapper->allocatorObj;

	PyMem_SetAllocator(PYMEM_DOMAIN_RAW, pythonAllocatorWrapper->allocatorRaw);
	PyMem_SetAllocator(PYMEM_DOMAIN_MEM, pythonAllocatorWrapper->allocatorMem);
	PyMem_SetAllocator(PYMEM_DOMAIN_OBJ, pythonAllocatorWrapper->allocatorObj);	
}

}