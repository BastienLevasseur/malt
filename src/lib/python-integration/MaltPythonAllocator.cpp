#include <iostream>
#include "MaltPythonAllocator.hpp"
#include "PythonAllocatorDomain.hpp"

namespace MALT{
static MaltPythonAllocator* gblMaltPythonAllocator = nullptr;

/**
 * Overlap for the PyMalloc, raw domain, malloc function. 
 */
static void* Malt_PyMem_RawMalloc(void* ctx, size_t size){

	//Reproduces the same behavior as the Python allocator
	if (size == 0){
		size = 1;
	}

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){		
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonAlloc(PYMEM_DOMAIN_RAW, size);
			gblMaltPythonAllocator->recursiveGuard = false;
		}else{
			gblMaltPythonAllocator->recursiveFault++;
		}
	}

	return gblMaltPythonAllocator->originalAllocatorRaw->malloc(ctx, size);
}

/**
 * Overlap for the PyMalloc, raw domain, Free function
 */
static void Malt_PyMem_RawFree(void* ctx, void* ptr){

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){		
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonFree(PYMEM_DOMAIN_RAW, ptr);
			gblMaltPythonAllocator->recursiveGuard = false;
		}else{
			gblMaltPythonAllocator->recursiveFault++;
		}
	}

	gblMaltPythonAllocator->originalAllocatorRaw->free(ctx, ptr);
}


/**
 * * Overlap for the Raw domain Calloc function
 */
static void* Malt_PyMem_RawCalloc(void* ctx, size_t nelem, size_t elsize){

	//Reproduces the same behavior as the Python allocator
	if (nelem == 0 || elsize == 0) {
        nelem = 1;
        elsize = 1;
    }

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonCalloc(PYMEM_DOMAIN_RAW, nelem, elsize);
			gblMaltPythonAllocator->recursiveGuard = false;
		}else{
			gblMaltPythonAllocator->recursiveFault++;
		}
	}

	return gblMaltPythonAllocator->originalAllocatorRaw->calloc(ctx, nelem, elsize);
}


/**
 * Overlap for the Raw domain Realloc function
 */
static void* Malt_PyMem_RawRealloc(void* ctx, void *ptr, size_t new_size){
	
	//Reproduces the same behavior as the Python allocator
	if (new_size == 0){
		new_size = 1;
	}

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonRealloc(PYMEM_DOMAIN_RAW, ptr, new_size);
			gblMaltPythonAllocator->recursiveGuard = false;
		}else{
			gblMaltPythonAllocator->recursiveFault++;
		}
	}

	return gblMaltPythonAllocator->originalAllocatorRaw->realloc(ctx, ptr, new_size);
}


/**
 * Overlap for the Mem domain Malloc function
 */
static void* Malt_PyMem_Malloc(void* ctx, size_t size){

	//Reproduces the same behavior as the Python allocator
	if (size == 0){
		size = 1;
	}

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonAlloc(PYMEM_DOMAIN_MEM, size);
			gblMaltPythonAllocator->recursiveGuard = false;
		}else{
			gblMaltPythonAllocator->recursiveFault++;
		}
	}

	return gblMaltPythonAllocator->originalAllocatorMem->malloc(ctx, size);
}


/**
 * Overlap for the Mem domain Free function
 */
static void Malt_PyMem_Free(void* ctx, void* ptr){

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonFree(PYMEM_DOMAIN_MEM, ptr);
			gblMaltPythonAllocator->recursiveGuard = false;
		}else{
			gblMaltPythonAllocator->recursiveFault++;
		}
	}

	return gblMaltPythonAllocator->originalAllocatorMem->free(ctx, ptr);
}


/**
 * Overlap for the Mem domain Calloc function
 */
static void* Malt_PyMem_Calloc(void* ctx, size_t nelem, size_t elsize){

	//Reproduces the same behavior as the Python allocator
	if (nelem == 0 || elsize == 0) {
        nelem = 1;
        elsize = 1;
    }

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonCalloc(PYMEM_DOMAIN_MEM, nelem, elsize);
			gblMaltPythonAllocator->recursiveGuard = false;	
		}else{
			gblMaltPythonAllocator->recursiveFault++;
		}
	}

	return gblMaltPythonAllocator->originalAllocatorMem->calloc(ctx, nelem, elsize);
}


/**
 * Overlap for the Mem domain Realloc function
 */
static void* Malt_PyMem_Realloc(void* ctx, void *ptr, size_t new_size){

	//Reproduces the same behavior as the Python allocator
	if (new_size == 0){
		new_size = 1;
	}

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonRealloc(PYMEM_DOMAIN_MEM, ptr, new_size);
			gblMaltPythonAllocator->recursiveGuard = false;
		}else{
			gblMaltPythonAllocator->recursiveFault++;
		}
	}

	return gblMaltPythonAllocator->originalAllocatorMem->realloc(ctx, ptr, new_size);
}


/**
 * Overlap for the Obj domain Malloc function
 */
static void* Malt_PyObject_Malloc(void* ctx, size_t size){

	//Reproduces the same behavior as the Python allocator
	if (size == 0){
		size = 1;
	}

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonAlloc(PYMEM_DOMAIN_OBJ, size);
			gblMaltPythonAllocator->recursiveGuard = false;
		}else{
			gblMaltPythonAllocator->recursiveFault++;
		}
	}

	return gblMaltPythonAllocator->originalAllocatorObj->malloc(ctx, size);
}


/**
 * Overlap for the Obj domain Free function
 */
static void Malt_PyObject_Free(void* ctx, void* ptr){

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonFree(PYMEM_DOMAIN_OBJ, ptr);
			gblMaltPythonAllocator->recursiveGuard = false;	
		}else{
			gblMaltPythonAllocator->recursiveFault++;
		}
	}

	return gblMaltPythonAllocator->originalAllocatorObj->free(ctx, ptr);
}


/**
 * Overlap for the Mem domain Calloc function
 */
static void* Malt_PyObject_Calloc(void* ctx, size_t nelem, size_t elsize){

	if (nelem == 0 || elsize == 0) {
        nelem = 1;
        elsize = 1;
    }

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonCalloc(PYMEM_DOMAIN_OBJ, nelem, elsize);
			gblMaltPythonAllocator->recursiveGuard = false;	
		}else{
			gblMaltPythonAllocator->recursiveFault++;
		}
	}

	return gblMaltPythonAllocator->originalAllocatorObj->calloc(ctx, nelem, elsize);
}


/**
 * Overlap for the Mem domain Realloc function
 */
static void* Malt_PyObject_Realloc(void* ctx, void *ptr, size_t new_size){

	//Reproduces the same behavior as the Python allocator
	if (new_size == 0){
		new_size = 1;
	}

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonRealloc(PYMEM_DOMAIN_OBJ, ptr, new_size);
			gblMaltPythonAllocator->recursiveGuard = false;
		}else{
			gblMaltPythonAllocator->recursiveFault++;
		}
	}

	return gblMaltPythonAllocator->originalAllocatorObj->realloc(ctx, ptr, new_size);
}

/**
 * Constructor for the custom allocator, fetches the Python original allocator and initialises the custom malt Python allocator
 * that will profile incomming Python's malloc/free/calloc/realloc
 */
MaltPythonAllocator_t* initialiseMaltPythonAllocator(PythonHandler* pythonHandler){
	assert(gblMaltPythonAllocator == nullptr);
	gblMaltPythonAllocator = new MaltPythonAllocator();

	gblMaltPythonAllocator->maltPythonHandler = pythonHandler;

	//Init the original Python allocator
	gblMaltPythonAllocator->originalAllocatorRaw = new PythonAllocatorPerDomain();
	gblMaltPythonAllocator->originalAllocatorMem = new PythonAllocatorPerDomain();
	gblMaltPythonAllocator->originalAllocatorObj = new PythonAllocatorPerDomain();

	//Populate it with the orginal allocator function pointers
	PyMem_GetAllocator(PYMEM_DOMAIN_RAW, gblMaltPythonAllocator->originalAllocatorRaw);
	PyMem_GetAllocator(PYMEM_DOMAIN_MEM, gblMaltPythonAllocator->originalAllocatorMem);
	PyMem_GetAllocator(PYMEM_DOMAIN_OBJ, gblMaltPythonAllocator->originalAllocatorObj);

	//Init our MALT custom Python allocator
	gblMaltPythonAllocator->maltAllocatorRaw = new PythonAllocatorPerDomain();
	gblMaltPythonAllocator->maltAllocatorMem = new PythonAllocatorPerDomain();
	gblMaltPythonAllocator->maltAllocatorObj = new PythonAllocatorPerDomain();

	//Populate it with our own functions for each domain
	//Raw Domain
	gblMaltPythonAllocator->maltAllocatorRaw->malloc = Malt_PyMem_RawMalloc;
	gblMaltPythonAllocator->maltAllocatorRaw->free = Malt_PyMem_RawFree;
	gblMaltPythonAllocator->maltAllocatorRaw->calloc = Malt_PyMem_RawCalloc;
	gblMaltPythonAllocator->maltAllocatorRaw->realloc = Malt_PyMem_RawRealloc;

	//Mem domain
	gblMaltPythonAllocator->maltAllocatorMem->malloc = Malt_PyMem_Malloc;
	gblMaltPythonAllocator->maltAllocatorMem->free = Malt_PyMem_Free;
	gblMaltPythonAllocator->maltAllocatorMem->calloc = Malt_PyMem_Calloc;
	gblMaltPythonAllocator->maltAllocatorMem->realloc = Malt_PyMem_Realloc;

	//Obj domain
	gblMaltPythonAllocator->maltAllocatorObj->malloc = Malt_PyObject_Malloc;
	gblMaltPythonAllocator->maltAllocatorObj->free = Malt_PyObject_Free;
	gblMaltPythonAllocator->maltAllocatorObj->calloc = Malt_PyObject_Calloc;
	gblMaltPythonAllocator->maltAllocatorObj->realloc = Malt_PyObject_Realloc;

	//Set the allocator into the Python Interpreter
	PyMem_SetAllocator(PYMEM_DOMAIN_RAW, gblMaltPythonAllocator->maltAllocatorRaw);
	PyMem_SetAllocator(PYMEM_DOMAIN_MEM, gblMaltPythonAllocator->maltAllocatorMem);
	PyMem_SetAllocator(PYMEM_DOMAIN_OBJ, gblMaltPythonAllocator->maltAllocatorObj);

	return gblMaltPythonAllocator;
}


/**
 * Destroys MALT custom Python allocator
 * It needs to be disabled beforehand
 */
void destroyMaltPythonAllocator(MaltPythonAllocator_t* maltAllocator){
	assert(maltAllocator->enabledFlag == false);
	assert(maltAllocator->recursiveGuard == false);

	//First the malt custom allocator
	delete maltAllocator->maltAllocatorRaw;
	delete maltAllocator->maltAllocatorMem;
	delete maltAllocator->maltAllocatorObj;

	//Then the original Python allocator
	delete maltAllocator->originalAllocatorRaw;
	delete maltAllocator->originalAllocatorMem;
	delete maltAllocator->originalAllocatorObj;

	maltAllocator = nullptr;
}


/**
 * Enables MALT custom Python Allocator
 */
void enableMaltPythonAllocator(MaltPythonAllocator_t* maltAllocator){
	assert(gblMaltPythonAllocator->enabledFlag == false);
	maltAllocator->enabledFlag = true;

	//Set MALT custom Python allocator as the Python allocator
	PyMem_SetAllocator(PYMEM_DOMAIN_RAW, maltAllocator->maltAllocatorRaw);
	PyMem_SetAllocator(PYMEM_DOMAIN_MEM, maltAllocator->maltAllocatorMem);
	PyMem_SetAllocator(PYMEM_DOMAIN_OBJ, maltAllocator->maltAllocatorObj);
}


/**
 * Disables MALT custom Python Allocator
 */
void disableMaltPythonAllocator(MaltPythonAllocator_t* maltAllocator){
	assert(maltAllocator->enabledFlag == true);
	maltAllocator->enabledFlag = false;

	//Set the Original Python allocator as the Python allocator i.e: removes MALT Python allocator
	PyMem_SetAllocator(PYMEM_DOMAIN_RAW, maltAllocator->originalAllocatorRaw);
	PyMem_SetAllocator(PYMEM_DOMAIN_MEM, maltAllocator->originalAllocatorMem);
	PyMem_SetAllocator(PYMEM_DOMAIN_OBJ, maltAllocator->originalAllocatorObj);
}

/**
 * FIXME: Debbuging purposes, will be removed
 */
void printRecursiveFault(MaltPythonAllocator_t* maltAllocator){
	std::cout << maltAllocator->recursiveFault << " recursive faults" << std::endl;
}
}