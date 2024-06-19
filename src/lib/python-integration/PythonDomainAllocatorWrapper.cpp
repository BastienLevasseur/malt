#include "PythonDomainAllocatorWrapper.hpp"

namespace MALT {

    PythonDomainAllocatorWrapper::PythonDomainAllocatorWrapper(PythonHandler* pythonHandler, PythonAllocatorDomainType domain, PythonGuard* guard, PythonAllocatorDomain* originalAllocator){
        this->pythonHandler = pythonHandler;
        this->domain = domain;
        this->guard = guard;
        this->originalAllocator = originalAllocator;
    }

    PythonDomainAllocatorWrapper::~PythonDomainAllocatorWrapper(){
        ;
    }

    /* If size (re)alloced is zero we allocate one byte to avoid returning NULL */
    /* We do not modify the parameters to avoid changing the behavior of the original Python allocator */

    void* PythonDomainAllocatorWrapper::onMalloc(void* context, size_t size){

        size_t alloced_size = size; 
        if (alloced_size == 0){
		    alloced_size = 1;
	    }
        
        if(this->guard->enterOnce()){
            this->pythonHandler->maltLogPythonAlloc(this->domain, alloced_size);
            this->guard->exit();
        }

        return this->originalAllocator->malloc(context, size);
    }


    void PythonDomainAllocatorWrapper::onFree(void* context, void* ptr){

        if(this->guard->enterOnce()){
            this->pythonHandler->maltLogPythonFree(this->domain, ptr);
            this->guard->exit();
        }
        return this->originalAllocator->free(context, ptr);
    }


    void* PythonDomainAllocatorWrapper::onCalloc(void* context, size_t nelem, size_t elsize){

        size_t nelem_alloced = nelem;
        size_t elsize_alloced = elsize;

        if ((nelem == 0) || (elsize == 0)){
            nelem_alloced = 1;
            elsize_alloced = 1;
        }

        if(this->guard->enterOnce()){
            this->pythonHandler->maltLogPythonCalloc(this->domain, nelem_alloced, elsize_alloced);
            this->guard->exit();
        }

        return this->originalAllocator->calloc(context, nelem, elsize);
    }


    void* PythonDomainAllocatorWrapper::onRealloc(void* context, void* ptr, size_t size){

        size_t size_alloced = size;
        if (size == 0){
            size_alloced = 1;
        }
        
        if(this->guard->enterOnce()){
            this->pythonHandler->maltLogPythonRealloc(this->domain, ptr, size_alloced);
            this->guard->exit();
        }

        return this->originalAllocator->realloc(context, ptr, size);
    }
}