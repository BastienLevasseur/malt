#include <iostream>
#include "MaltPythonAllocator.hpp"
#include "PythonAllocatorDomain.hpp"

namespace MALT{
static MaltPythonAllocator_t* gblMaltPythonAllocator = nullptr;

/* If size (re)alloced is zero we allocate one byte to avoid returning NULL */

/**
 * Overlap for the PyMalloc, raw domain, malloc function. 
*/
void* Malt_PyMem_RawMalloc(void* ctx, size_t size){

	
	size_t alloced_size = size; 
	if (alloced_size == 0){
		alloced_size = 1;
	}

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){		
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonAlloc(PYMEM_DOMAIN_RAW, alloced_size);
			gblMaltPythonAllocator->recursiveGuard = false;
		}
	}

	return gblMaltPythonAllocator->originalAllocator->allocatorRaw->malloc(ctx, size);
}

/**
 * Overlap for the PyMalloc, raw domain, Free function
 */
void Malt_PyMem_RawFree(void* ctx, void* ptr){

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){		
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonFree(PYMEM_DOMAIN_RAW, ptr);
			gblMaltPythonAllocator->recursiveGuard = false;
		}
	}

	gblMaltPythonAllocator->originalAllocator->allocatorRaw->free(ctx, ptr);
}


/**
 * * Overlap for the Raw domain Calloc function
 */
void* Malt_PyMem_RawCalloc(void* ctx, size_t nelem, size_t elsize){

	
	size_t alloced_nelem = nelem;
	size_t alloced_elsize = elsize;
	if (alloced_nelem == 0 || alloced_elsize == 0) {
        alloced_nelem = 1;
        alloced_elsize = 1;
    }

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonCalloc(PYMEM_DOMAIN_RAW, alloced_nelem, alloced_elsize);
			gblMaltPythonAllocator->recursiveGuard = false;
		}
	}

	return gblMaltPythonAllocator->originalAllocator->allocatorRaw->calloc(ctx, nelem, elsize);
}


/**
 * Overlap for the Raw domain Realloc function
 */
void* Malt_PyMem_RawRealloc(void* ctx, void *ptr, size_t new_size){
	
	
	size_t alloced_new_size = new_size;
	if (alloced_new_size == 0){
		alloced_new_size = 1;
	}

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonRealloc(PYMEM_DOMAIN_RAW, ptr, alloced_new_size);
			gblMaltPythonAllocator->recursiveGuard = false;
		}
	}

	return gblMaltPythonAllocator->originalAllocator->allocatorRaw->realloc(ctx, ptr, new_size);
}


/**
 * Overlap for the Mem domain Malloc function
 */
void* Malt_PyMem_Malloc(void* ctx, size_t size){

	
	size_t alloced_size = size; 
	if (alloced_size == 0){
		alloced_size = 1;
	}

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonAlloc(PYMEM_DOMAIN_MEM, alloced_size);
			gblMaltPythonAllocator->recursiveGuard = false;
		}
	}

	return gblMaltPythonAllocator->originalAllocator->allocatorMem->malloc(ctx, size);
}


/**
 * Overlap for the Mem domain Free function
 */
void Malt_PyMem_Free(void* ctx, void* ptr){

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonFree(PYMEM_DOMAIN_MEM, ptr);
			gblMaltPythonAllocator->recursiveGuard = false;
		}
	}

	return gblMaltPythonAllocator->originalAllocator->allocatorMem->free(ctx, ptr);
}


/**
 * Overlap for the Mem domain Calloc function
 */
void* Malt_PyMem_Calloc(void* ctx, size_t nelem, size_t elsize){

	
	size_t alloced_nelem = nelem;
	size_t alloced_elsize = elsize;
	if (alloced_nelem == 0 || alloced_elsize == 0) {
        alloced_nelem = 1;
        alloced_elsize = 1;
    }

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonCalloc(PYMEM_DOMAIN_MEM, alloced_nelem, alloced_elsize);
			gblMaltPythonAllocator->recursiveGuard = false;	
		}
	}

	return gblMaltPythonAllocator->originalAllocator->allocatorMem->calloc(ctx, nelem, elsize);
}


/**
 * Overlap for the Mem domain Realloc function
 */
void* Malt_PyMem_Realloc(void* ctx, void *ptr, size_t new_size){

	
	size_t alloced_new_size = new_size;
	if (new_size == 0){
		alloced_new_size = 1;
	}

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonRealloc(PYMEM_DOMAIN_MEM, ptr, alloced_new_size);
			gblMaltPythonAllocator->recursiveGuard = false;
		}
	}

	return gblMaltPythonAllocator->originalAllocator->allocatorMem->realloc(ctx, ptr, new_size);
}


/**
 * Overlap for the Obj domain Malloc function
 */
void* Malt_PyObject_Malloc(void* ctx, size_t size){

	
	size_t alloced_size = size; 
	if (alloced_size == 0){
		alloced_size = 1;
	}

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonAlloc(PYMEM_DOMAIN_OBJ, alloced_size);
			gblMaltPythonAllocator->recursiveGuard = false;
		}
	}

	return gblMaltPythonAllocator->originalAllocator->allocatorObj->malloc(ctx, size);
}


/**
 * Overlap for the Obj domain Free function
 */
void Malt_PyObject_Free(void* ctx, void* ptr){

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonFree(PYMEM_DOMAIN_OBJ, ptr);
			gblMaltPythonAllocator->recursiveGuard = false;	
		}
	}

	return gblMaltPythonAllocator->originalAllocator->allocatorObj->free(ctx, ptr);
}


/**
 * Overlap for the Mem domain Calloc function
 */
void* Malt_PyObject_Calloc(void* ctx, size_t nelem, size_t elsize){

	size_t alloced_nelem = nelem;
	size_t alloced_elsize = elsize;
	if (alloced_nelem == 0 || alloced_elsize == 0) {
        alloced_nelem = 1;
        alloced_elsize = 1;
    }

	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonCalloc(PYMEM_DOMAIN_OBJ, alloced_nelem, alloced_elsize);
			gblMaltPythonAllocator->recursiveGuard = false;	
		}
	}

	return gblMaltPythonAllocator->originalAllocator->allocatorObj->calloc(ctx, nelem, elsize);
}


/**
 * Overlap for the Mem domain Realloc function
 */
void* Malt_PyObject_Realloc(void* ctx, void *ptr, size_t new_size){

	size_t alloced_new_size = new_size;
	if (alloced_new_size == 0){
		alloced_new_size = 1;
	}


	if (gblMaltPythonAllocator->enabledFlag == true){
		if (gblMaltPythonAllocator->recursiveGuard == false){
			gblMaltPythonAllocator->recursiveGuard = true;
			gblMaltPythonAllocator->maltPythonHandler->maltLogPythonRealloc(PYMEM_DOMAIN_OBJ, ptr, alloced_new_size);
			gblMaltPythonAllocator->recursiveGuard = false;
		}
	}

	return gblMaltPythonAllocator->originalAllocator->allocatorObj->realloc(ctx, ptr, new_size);
}

/* Get the three Python allocators corresponding to the three domains */
void getPythonAllocatorFunctions(PythonAllocator_t* pythonAllocator){
	PyMem_GetAllocator(PYMEM_DOMAIN_RAW, pythonAllocator->allocatorRaw);
	PyMem_GetAllocator(PYMEM_DOMAIN_MEM, pythonAllocator->allocatorMem);
	PyMem_GetAllocator(PYMEM_DOMAIN_OBJ, pythonAllocator->allocatorObj);
}


/* Set the three Python allocators corresponding to the three domains */
void setPythonAllocatorFunctions(PythonAllocator_t* pythonAllocator){
	PyMem_SetAllocator(PYMEM_DOMAIN_RAW, pythonAllocator->allocatorRaw);
	PyMem_SetAllocator(PYMEM_DOMAIN_MEM, pythonAllocator->allocatorMem);
	PyMem_SetAllocator(PYMEM_DOMAIN_OBJ, pythonAllocator->allocatorObj);
}

/** Initialises a Python Allocator */
PythonAllocator_t* initialisePythonAllocator(){
	PythonAllocator_t* pythonAllocator = new PythonAllocator_t();
	pythonAllocator->allocatorRaw = new PythonAllocatorPerDomain();
	pythonAllocator->allocatorMem = new PythonAllocatorPerDomain();
	pythonAllocator->allocatorObj = new PythonAllocatorPerDomain();
	return pythonAllocator;
}

/** Destroys a Python Allocator */
void destroyPythonAllocator(PythonAllocator_t* pythonAllocator){
	assert(pythonAllocator != nullptr);
	delete pythonAllocator->allocatorObj;
	delete pythonAllocator->allocatorMem;
	delete pythonAllocator->allocatorRaw;
	delete pythonAllocator;
}


/**
 * Constructor for the custom allocator, fetches the Python original allocator and initialises the custom malt Python allocator
 * that will profile incomming Python's malloc/free/calloc/realloc
 */
void initialiseMaltPythonAllocator(PythonHandler* pythonHandler){
	assert(gblMaltPythonAllocator == nullptr);
	gblMaltPythonAllocator = new MaltPythonAllocator_t();

	gblMaltPythonAllocator->maltPythonHandler = pythonHandler;

	//Init the original Python allocator
	gblMaltPythonAllocator->originalAllocator = initialisePythonAllocator();
	
	//Populate it with the orginal allocator function pointers
	getPythonAllocatorFunctions(gblMaltPythonAllocator->originalAllocator);
	
	//Init our MALT custom Python allocator
	gblMaltPythonAllocator->customAllocator = initialisePythonAllocator();

	//Populate it with our own functions for each domain
	//Raw Domain
	gblMaltPythonAllocator->customAllocator->allocatorRaw->malloc = Malt_PyMem_RawMalloc;
	gblMaltPythonAllocator->customAllocator->allocatorRaw->free = Malt_PyMem_RawFree;
	gblMaltPythonAllocator->customAllocator->allocatorRaw->calloc = Malt_PyMem_RawCalloc;
	gblMaltPythonAllocator->customAllocator->allocatorRaw->realloc = Malt_PyMem_RawRealloc;

	//Mem domain
	gblMaltPythonAllocator->customAllocator->allocatorMem->malloc = Malt_PyMem_Malloc;
	gblMaltPythonAllocator->customAllocator->allocatorMem->free = Malt_PyMem_Free;
	gblMaltPythonAllocator->customAllocator->allocatorMem->calloc = Malt_PyMem_Calloc;
	gblMaltPythonAllocator->customAllocator->allocatorMem->realloc = Malt_PyMem_Realloc;

	//Obj domain
	gblMaltPythonAllocator->customAllocator->allocatorObj->malloc = Malt_PyObject_Malloc;
	gblMaltPythonAllocator->customAllocator->allocatorObj->free = Malt_PyObject_Free;
	gblMaltPythonAllocator->customAllocator->allocatorObj->calloc = Malt_PyObject_Calloc;
	gblMaltPythonAllocator->customAllocator->allocatorObj->realloc = Malt_PyObject_Realloc;

	gblMaltPythonAllocator->recursiveGuard = false;
	gblMaltPythonAllocator->enabledFlag = false;
}


/**
 * Destroys MALT custom Python allocator
 * It needs to be disabled beforehand
 */
void destroyMaltPythonAllocator(MaltPythonAllocator_t* maltPythonAllocator){
	assert(maltPythonAllocator->enabledFlag == false);
	assert(maltPythonAllocator->recursiveGuard == false);

	destroyPythonAllocator(maltPythonAllocator->customAllocator);
	destroyPythonAllocator(maltPythonAllocator->originalAllocator);
	maltPythonAllocator->maltPythonHandler = nullptr;
	
	delete maltPythonAllocator;
}


/**
 * Enables MALT custom Python Allocator
 */
void enableMaltPythonAllocator(MaltPythonAllocator_t* maltPythonAllocator){
	assert(maltPythonAllocator != nullptr);
	assert(maltPythonAllocator->enabledFlag == false);
	maltPythonAllocator->enabledFlag = true;

	std::cout << "Setting the allocators..." << std::endl;
	//Set MALT custom Python allocator as the Python allocator
	setPythonAllocatorFunctions(maltPythonAllocator->customAllocator);
}


/**
 * Disables MALT custom Python Allocator
 */
void disableMaltPythonAllocator(MaltPythonAllocator_t* maltPythonAllocator){
	assert(maltPythonAllocator->enabledFlag == true);
	maltPythonAllocator->enabledFlag = false;

	//Set the Original Python allocator as the Python allocator i.e: removes MALT Python allocator
	setPythonAllocatorFunctions(maltPythonAllocator->originalAllocator);
}


MaltPythonAllocator_t* getGlobalMaltPythonAllocator(){
	return gblMaltPythonAllocator;
}

}